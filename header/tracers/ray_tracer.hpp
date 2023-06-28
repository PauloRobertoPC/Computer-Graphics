#ifndef RAY_TRACING_HPP
#define RAY_TRACING_HPP

#include "tracer.hpp"

class ray_tracer : public tracer
{
    std::tuple<px, object*> trace_ray(ray r) const;
    std::tuple<px, object*> trace_ray(ray r, const int depth) const;
    std::tuple<px, object*> trace_ray(ray r, float& tmin, const int depth) const;
};

#endif
