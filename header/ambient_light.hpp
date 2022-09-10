#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include "light.hpp"

class ambient_light : public light {
    public:
        ambient_light(px intensity);
    
        px calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate);
        vp get_l(vp P);
};

#endif
