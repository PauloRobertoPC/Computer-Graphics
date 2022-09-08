#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "px.hpp"
#include "vp.hpp"
#include <tuple>

class sphere : public object{
    private:
        vp center; double radio, specular; px color;
     
    public:
        sphere();
        sphere(vp center, double r, double s, px color);
        sphere(double x, double y, double z, double r, double s, px color);

        //calculate the intersections between the sphere and the ray
        std::tuple<double, double> intersection_with_ray(vp O, vp D);
    
        vp normal(vp P);
    
        //Getters and Setters
        vp get_center();
        void set_center(vp center);
        double get_radio();
        void set_radio(double radio);
        double get_specular();
        void set_specular(double specular);
        px get_color();
        void set_color(px color);
};

#endif
