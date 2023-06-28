#ifndef HIT_INFO_HPP
#define HIT_INFO_HPP

#include "vp.hpp"
#include "px.hpp"
#include "../objects/object.hpp"
#include "../utils/ray.hpp"

class hit_info{

public:
    bool hit_an_object;
    // Material* material_ptr;
    vp hit_point;
    vp local_hit_point;
    vp normal;
    px color;
    ray r; //ray
    int depth;
    vp dir; //direction light
    object* closest_object;
    double t;
    // World& w;
    // ShadeRec(World& wr);
    // ShadeRec(const ShadeRec& sr);

    hit_info();
};

#endif
