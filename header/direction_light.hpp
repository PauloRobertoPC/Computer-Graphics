#ifndef DIRECTION_LIGHT_HPP
#define DIRECTION_LIGHT_HPP

#include "specular_light.hpp"

class direction_light : public specular_light {
    private:
        vp direction; 
        
    public:
        direction_light(double intensity, vp direction);
    
        double calculate_intensity(vp P, vp N, vp V, int s);
    
        vp get_direction();
        void set_direction(vp direction);
};

#endif

