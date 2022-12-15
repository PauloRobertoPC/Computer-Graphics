#ifndef SPECULAR_LIGHT_HPP
#define SPECULAR_LIGHT_HPP

#include "vp.hpp"
#include "light.hpp"

class specular_light : public light
{
public:
    specular_light(px intensity, char type_l = 'c');

    px specular(vp N, vp L, vp V, object *obj);
    void change_angle(double a);
    void change_direction(vp d);
};

#endif
