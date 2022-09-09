#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "specular_light.hpp"

class point_light : public specular_light {
    private:
        vp position; 
        
    public:
        point_light(double intensity, vp position);
    
        double calculate_intensity(vp P, vp N, vp V, int s);
    
        vp get_position();
        void set_position(vp position);
};

#endif