#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "vp.hpp"
#include "object.hpp"

class light{
    private: 
        px intensity;

    public:
        light(px intensity);

        virtual px calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate) = 0;
        virtual vp get_l(vp P) = 0;

        //transformations
        virtual void to_camera(matrix M) = 0;
    
        px get_intensity();
        void set_intensity(px intensity);
};

#endif
