#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "vp.hpp"
#include "object.hpp"

class light
{
private:
    px intensity;
    px save_intensity;

protected:
    matrix transformations;

public:
    light(px intensity);

    virtual px calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate) = 0;
    virtual vp get_l(vp P) = 0;

    // transformations
    virtual void to_camera(matrix M) = 0;
    virtual void change_angle(double a) = 0;
    virtual void change_direction(vp d) = 0;

    px get_intensity();
    void set_intensity(px intensity);

    virtual void translation(vp v) = 0;
    virtual void print_light() = 0;

    void turn_off();
    void turn_on();
    void turn_on(px intensity);
};

#endif
