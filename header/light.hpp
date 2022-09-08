#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "vp.hpp"

class light{
    private: 
        double intensity;

    public:
        light(double intensity);

        virtual double calculate_intensity(vp P, vp N, vp V, int s) = 0;
        
        double get_intensity();
        void set_intensity(double intensity);
};

#endif
