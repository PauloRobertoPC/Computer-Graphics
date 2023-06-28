#ifndef TRACER_HPP
#define TRACER_HPP

#include "../utils/vp.hpp"
#include "../utils/px.hpp"
#include "../utils/ray.hpp"
#include "../objects/object.hpp"
#include "../world/scene.hpp"

class tracer{

public:
    tracer();

    virtual std::tuple<px, object*> trace_ray(ray r) const;
    virtual std::tuple<px, object*> trace_ray(ray r, const int depth) const;
    virtual std::tuple<px, object*> trace_ray(ray r, float& tmin, const int depth) const;

    void set_scene(scene* scn);

protected:
    scene *sc;
};

#endif
