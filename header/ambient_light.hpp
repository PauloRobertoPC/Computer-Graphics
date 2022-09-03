#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include "light.hpp"

class ambient_light : public light {
    public:
        ambient_light(double intensity);
    
        double calculate_intensity(vp P, vp N, vp V, int s);
};

#endif
