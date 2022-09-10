#ifndef DIRECTION_LIGHT_HPP
#define DIRECTION_LIGHT_HPP

#include "specular_light.hpp"

class direction_light : public specular_light {
    private:
        vp direction; 
        
    public:
        direction_light(px intensity, vp direction);
    
        px calculate_intensity(vp P, vp N, vp V, object* obj, bool calculate);
        vp get_l(vp P);
    
        vp get_direction();
        void set_direction(vp direction);
};

#endif

