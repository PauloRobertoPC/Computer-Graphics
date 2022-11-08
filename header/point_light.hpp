#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "specular_light.hpp"

class point_light : public specular_light {
    private:
        vp position; 
        
    public:
        point_light(px intensity, vp position);
    
        //transformations
        void to_camera(matrix M);
    
        px calculate_intensity(vp P, vp N, vp V, object* obj, bool calculate);
        vp get_l(vp P);
    
        vp get_position();
        void set_position(vp position);

        void translation(vp v);
        void print_light();
};

#endif
