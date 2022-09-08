#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <tuple>
#include "vp.hpp"
#include "px.hpp"

class object{
    private:
        px color; double specular;  
    
    public:
        object(); 
        object(px color, double specular);
    
        virtual std::tuple<double, double> intersection_with_ray(vp O, vp D) = 0;
        virtual vp normal(vp P) = 0;

        //Getters and Setters
        px get_color();
        void set_color(px color);
        double get_specular();
        void set_specular(double specular);
};

#endif
