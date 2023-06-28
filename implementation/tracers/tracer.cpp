#include "../../header/tracers/tracer.hpp"

tracer::tracer(){
}

std::tuple<px, object*> tracer::trace_ray(ray r) const{
    return {px(0, 0, 0), nullptr};
}

std::tuple<px, object*> tracer::trace_ray(ray r, const int depth) const{
    return {px(0, 0, 0), nullptr};
}

std::tuple<px, object*> tracer::trace_ray(ray r, float& tmin, const int depth) const{
    return {px(0, 0, 0), nullptr};
}

void tracer::set_scene(scene* scn){
    sc = scn;
}
