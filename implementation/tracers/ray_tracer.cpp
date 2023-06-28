#include "../../header/tracers/ray_tracer.hpp"

double mix(double a, double b, double mix)
{
    return b * mix + a * (1 - mix);
}

std::tuple<px, object*> ray_tracer::trace_ray(ray r) const{
    float tmin = 0.001;
    return trace_ray(r, tmin, 0);
}

std::tuple<px, object*> ray_tracer::trace_ray(ray r, const int depth) const{
    float tmin = 0.001;
    return trace_ray(r, tmin, depth);
}

std::tuple<px, object*> ray_tracer::trace_ray(ray r, float& tmin, const int depth) const{
    double ni = 1.0003;
    double tmax = INF;
    int i = 0, j = 0;

    hit_info hi = sc->hit_objects(r, tmin, depth);

    if(!hi.hit_an_object)
        return {sc->c.get_background_color(), hi.closest_object};

    px local_color = sc->compute_lighting(hi.hit_point, hi.normal, -r.D, hi.closest_object);

    // Difuse Object
    if(depth <= 0 || (comparator::eq(hi.closest_object->get_reflective(), 0.0) && comparator::eq(hi.closest_object->get_transparency(), 0.0)))
        return {local_color, hi.closest_object};

    vp refle_ray = ray::reflection_ray(-r.D, hi.normal);
    vp refra_ray = ray::refracted_ray(-r.D, hi.normal, ni, hi.closest_object->get_ni());
    // vp refra_ray = refractRay(D, P, n, closest_object);
    px refle_color(0, 0, 0), refra_color(0, 0, 0), final_color(0, 0, 0);
    object *aux_object;

    if(comparator::neq(hi.closest_object->get_reflective(), 0.0) && comparator::neq(hi.closest_object->get_transparency(), 0)){
        std::tie(refle_color, aux_object) = trace_ray(ray(hi.hit_point, refle_ray), tmin, depth-1);
        std::tie(refra_color, aux_object) = trace_ray(ray(hi.hit_point, refra_ray), tmin, depth-1);

        // Fresnel Effect
        double facingratio = -r.D*hi.normal;
        double fr = mix(pow(1 - facingratio, 3), 1, 0.1);

        final_color =  refra_color*(1-fr) + refle_color*fr;
        final_color = final_color + local_color*(1-hi.closest_object->get_transparency());
    }else if(comparator::neq(hi.closest_object->get_reflective(), 0.0)) {
        std::tie(refle_color, aux_object) = trace_ray(ray(hi.hit_point, refle_ray), tmin, depth-1);
        final_color = (local_color)*(1-hi.closest_object->get_reflective()) + refle_color*hi.closest_object->get_reflective();
    }else if(comparator::neq(hi.closest_object->get_transparency(), 0)){
        std::tie(refra_color, aux_object) = trace_ray(ray(hi.hit_point, refra_ray), tmin, depth-1);
        final_color = local_color*(1-hi.closest_object->get_transparency()) + refra_color*hi.closest_object->get_transparency();
    }else{
        final_color = local_color;
    }

    return {final_color, hi.closest_object};
}
