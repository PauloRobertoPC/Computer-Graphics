#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "specular_light.hpp"

class spot_light : public specular_light
{
private:
    vp position, direction;
    double angle;

public:
    spot_light(px intensity, vp position, vp direction, double angle);

    // transformations
    void to_camera(matrix M);

    px calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate);
    vp get_l(vp P);

    void change_angle(double a);
    void change_direction(vp d);

    vp get_position();
    void set_position(vp position);
    vp get_direction();
    void set_direction(vp direction);

    void translation(vp v);
    void print_light();
};

#endif
