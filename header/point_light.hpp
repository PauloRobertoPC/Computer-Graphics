#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "specular_light.hpp"

class point_light : public specular_light
{
private:
    vp position;

public:
    point_light(px intensity, vp position, char type_l = 'p');

    // transformations
    void to_camera(matrix M);

    px calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate);
    vp get_l(vp P);

    void change_angle(double a);
    void change_direction(vp d);

    vp get_position();
    void set_position(vp position);

    void translation(vp v);
    void print_light();
};

#endif
