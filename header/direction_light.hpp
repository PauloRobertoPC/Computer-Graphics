#ifndef DIRECTION_LIGHT_HPP
#define DIRECTION_LIGHT_HPP

#include "specular_light.hpp"

class direction_light : public specular_light
{
private:
    vp direction;

public:
    direction_light(px intensity, vp direction, char type_l = 'd');

    // transformations
    void to_camera(matrix M);

    void change_angle(double a);
    void change_direction(vp d);

    px calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate);
    vp get_l(vp P);

    vp get_direction();
    void set_direction(vp direction);

    void translation(vp v);
    void print_light();
};

#endif
