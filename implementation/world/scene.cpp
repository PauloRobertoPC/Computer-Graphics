#include <bits/stdc++.h>
#include <cmath>
#include "../../header/world/scene.hpp"
#include "../../header/objects/plan.hpp"
#include "../../header/utils/comparator.hpp"
#include "../../header/cameras/camera.hpp"
#include "../../header/objects/plan.hpp"

scene::scene(camera O, viewport vw, canvas c, PROJECTION p) : O(O), vw(vw), c(c), p(p){}

bool scene::without_shade(vp P, light *l)
{
    double t, t_min = 1, t_max = INF, closest = INF;
    vp n;
    vp L = l->get_l(P);
    if ((~L) == 0.0)
        return true;
    vp NL = L / (~L);
    for (object *o : objects)
    {
        std::tie(t, n) = o->intersection_with_ray(P, NL, t_min, t_max);
        // if(t-EPS > t_min && t < t_max && t < closest) closest = t;
        if (comparator::g(t, t_min) && comparator::l(t, closest))
            closest = t;
    }

    if (l->type_l == 'd')
        return closest == INF;

    return (closest >= (~L));
}

vp scene::reflection_ray(vp R, vp N)
{
    vp RR = N * 2.0 * (N * R) - R;
    return (RR/(~RR));
}

vp scene::refracted_ray(vp I, vp N, double ni, double nt){
    double nr = ni/nt; 
    double dentro_raiz = 1-nr*nr*(1-(N*I)*(N*I)); 
    if(dentro_raiz < 0) return vp(0, 0, 0);
    vp T = N*(nr*(N*I) - sqrt(dentro_raiz)) - I*nr;
    return (T/(~T));
}

px scene::compute_lighting(vp P, vp N, vp V, object *obj)
{
    px i(0, 0, 0);
    for (light *l : lights)
        i = i + l->calculate_intensity(P, N, V, obj, without_shade(P, l));
    return i;
}

double mix(double a, double b, double mix)
{
    return b * mix + a * (1 - mix);
}

std::tuple<px, object *> scene::trace_ray(vp O, vp D, double t_min, double t_max, int i, int j, int recursion_depth, double ni)
{
    object *closest_object = nullptr;
    bool nulo = true;
    double t, closest = INF;
    vp aux, n;
    for (object *o : objects)
    {
        std::tie(t, aux) = o->intersection_with_ray(O, D, t_min, t_max);
        if (comparator::g(t, t_min) && comparator::l(t, t_max) && comparator::l(t, closest))
        {
            closest = t;
            n = aux;
            closest_object = o;
            nulo = false;
        }
    }

    if (nulo)
        return {c.get_background_color(), closest_object};
    if (closest_object->get_has_image())
        closest_object->set_pixel_image(i, j);

    vp P = O + D * closest;
    bool inside = false;
    if (comparator::g(D * n, 0))
        n = -n, inside = true;

    px local_color = compute_lighting(P, n, -D, closest_object);

    // Difuse Object
    if(recursion_depth <= 0 || (comparator::eq(closest_object->get_reflective(), 0.0) && comparator::eq(closest_object->get_transparency(), 0.0)))
        return {local_color, closest_object};

    vp refle_ray = reflection_ray(-D, n);
    vp refra_ray = refracted_ray(-D, n, ni, closest_object->get_ni());
    // vp refra_ray = refractRay(D, P, n, closest_object);
    px refle_color(0, 0, 0), refra_color(0, 0, 0), final_color(0, 0, 0);
    object *aux_object;

    if(comparator::neq(closest_object->get_reflective(), 0.0) && comparator::neq(closest_object->get_transparency(), 0)){
        std::tie(refle_color, aux_object) = trace_ray(P, refle_ray, t_min, t_max, i, j, recursion_depth-1, 1.0003);
        std::tie(refra_color, aux_object) = trace_ray(P, refra_ray, t_min, t_max, i, j, recursion_depth-1, 1.0003);

        // Fresnel Effect
        double facingratio = -D*n;
        double fr = mix(pow(1 - facingratio, 3), 1, 0.1);

        final_color =  refra_color*(1-fr) + refle_color*fr;
        final_color = final_color + local_color*(1-closest_object->get_transparency());
    }else if(comparator::neq(closest_object->get_reflective(), 0.0)) {
        std::tie(refle_color, aux_object) = trace_ray(P, refle_ray, t_min, t_max, i, j, recursion_depth-1, 1.0003);
        final_color = (local_color)*(1-closest_object->get_reflective()) + refle_color*closest_object->get_reflective();
    }else if(comparator::neq(closest_object->get_transparency(), 0)){
        std::tie(refra_color, aux_object) = trace_ray(P, refra_ray, t_min, t_max, i, j, recursion_depth-1, 1.0003);
        final_color = local_color*(1-closest_object->get_transparency()) + refra_color*closest_object->get_transparency();
    }else{
        final_color = local_color;
    }

    return {final_color, closest_object};
}

vp scene::xy(int i, int j)
{
    return vp(-vw.get_w() / 2.0 + vw.get_dx() / 2.0 + j * vw.get_dx(), vw.get_h() / 2.0 - vw.get_dy() / 2.0 - i * vw.get_dy(), vw.get_d());
}

void scene::add_object(object *o) { objects.insert(o); }
void scene::add_light(light *l) { lights.push_back(l); }

void scene::transform_scenario_to_camera()
{
    for (object *o : objects)
        o->to_camera(O.get_w2c());
    for (light *l : lights)
        l->to_camera(O.get_w2c());
}

void scene::transform_scenario_to_world()
{
    for (object *o : objects)
        o->to_camera(O.get_c2w());
    for (light *l : lights)
        l->to_camera(O.get_c2w());
}

double scene::rd(double min_max){
    const double lower_bound = -min_max;
    const double upper_bound = min_max;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    
    std::random_device rand_dev;          // Use random_device to get a random seed.
    // std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());

    std::mt19937 rand_engine(rand_dev()); // mt19937 is a good pseudo-random number 
                                          // generator.

    double x = unif(rand_engine);
    return x;
}


std::tuple<vp, vp> scene::ray_equation(int i, int j)
{
    vp D = xy(i, j);

    point_2D p2d = vw.sample_square();
    D.set_x(D.get_x()+p2d.x);
    D.set_y(D.get_y()+p2d.y);

    switch (this->p)
    {
    case PERSPECITVE:
        return {vp(0, 0, 0), (D / (~D))};
        break;
    case PARALELL:
        return {D, vp(0, 0, -1)};
        break;
    }
    return {vp(0, 0, 0), vp(0, 0, 0)};
}

void scene::change_projection(PROJECTION p)
{
    this->p = p;
}

void scene::draw_scenario(bool change_coordinates, int recursion_depth)
{
    if (change_coordinates)
        transform_scenario_to_camera();
    px color;
    object *choosen_object;
    vp O, D;
    for (int i = 0; i < c.get_n(); i++)
    {
        for (int j = 0; j < c.get_m(); j++)
        {
            px acm = px(0, 0, 0);
            color = px(0, 0, 0);
            for(int k = 0; k < vw.qnt_samples(); k++){
                std::tie(O, D) = ray_equation(i, j);
                std::tie(color, choosen_object) = trace_ray(O, D, 0.001, INF, i, j, recursion_depth, 1.0003);
                acm = acm+color;
            }
            c.to_color(i, j, acm/vw.qnt_samples(), choosen_object);
        }
    }
    std::cout << "DESENHO CONCLUIDO\n";
}

object *scene::select_object(int i, int j) { return c.get_object(i, j); }
light *scene::select_light(int i)
{
    if (i > this->lights.size() && i < 1)
        return nullptr;
    return this->lights[i - 1];
}

void scene::print_lights()
{
    for (int i = 0; i < this->lights.size(); i++)
    {
        std::cout << '(' << i + 1 << ") - ";
        this->lights[i]->print_light();
        std::cout << std::endl;
    }
}

void scene::del_object(object *o)
{
    objects.erase(o);
}

void scene::change_view(vp E, vp look_at, vp up)
{
    this->transform_scenario_to_world();
    this->O.change_view(E, look_at, up);
    this->transform_scenario_to_camera();
}

void scene::change_vp(double w, double h)
{
    vw.set_wh(w, h);
}

void scene::change_d(double d)
{
    vw.set_d(d);
}

void scene::translation(object *choosen_object, int i, int j)
{
    plan p(choosen_object->get_def_point(), vp(0, 0, 1));
    vp n, O, D;
    std::tie(O, D) = ray_equation(i, j);
    double t;
    std::tie(t, n) = p.intersection_with_ray(O, D, 1, INF);
    vp P = D * t;
    P.print();
    choosen_object->translation(P);
}

px scene::get_pixel(int i, int j)
{
    return c.get_color(i, j);
}

void scene::save_scenario(const char *image_name)
{
    c.write_image(image_name);
}
