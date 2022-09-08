#ifndef PLAN_HPP
#define PLAN_HPP

#include "object.hpp"
#include "px.hpp"
#include "vp.hpp"
#include <tuple>

class plan : public object{
    private:
        vp p_pi, n;         //p_pi = Point in Plan, n = vector normal with the plan
        px color;           //plan's color
        double specular;    //specular reflection
     
    public:
        plan();
        plan(vp p_pi, vp n, double s, px color);

        //calculate the intersections between the plan and the ray
        std::tuple<double, double> intersection_with_ray(vp O, vp D);
    
        vp normal(vp P);
    
        //Getters and Setters
        vp get_p_pi();
        void set_p_pi(vp p_pi);
        vp get_n();
        void set_n(vp n);
};

#endif
