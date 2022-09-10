#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "px.hpp"
#include "vp.hpp"
#include <tuple>

class sphere : public object{
    private:
        vp center; double radio;
     
    public:
        sphere();
        sphere(vp center, double r, px k_a, px k_d, px k_s, double s);

        //calculate the intersections between the sphere and the ray
        std::tuple<double, double> intersection_with_ray(vp O, vp D);
    
        vp normal(vp P);
    
        //Getters and Setters
        vp get_center();
        void set_center(vp center);
        double get_radio();
        void set_radio(double radio);
};

#endif
