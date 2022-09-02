#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "util.hpp"

enum light_type {ambient, point, directional};

struct light{
    light_type type;
    double intensity;
    vp position, direction;

    light(light_type type, double intensity, vp pos_dir=vp(0, 0, 0)) : type(type), intensity(intensity){
        if(type == point) position = pos_dir;
        else if(type == directional) direction = pos_dir;
    }
};

#endif
