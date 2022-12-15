#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include "light.hpp"

class ambient_light : public light
{
public:
    ambient_light(px intensity);

    // transformations
    void to_camera(matrix M);

    px calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate);
    vp get_l(vp P);

    void translation(vp v);
    void print_light();

    void change_angle(double a);
    void change_direction(vp d);
};

#endif
