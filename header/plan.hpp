#ifndef PLAN_HPP
#define PLAN_HPP

#include "object.hpp"
#include "px.hpp"
#include "vp.hpp"
#include <tuple>

class plan : public object{
    private:
        vp p_pi, n;         //p_pi = Point in Plan, n = vector normal with the plan
     
    public:
        plan();
        plan(vp p_pi, vp n);
        plan(vp p_pi, vp n, px k_a, px k_d, px k_s, double s);

        std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);

        //transformations
        void transform();
    
        //Getters and Setters
        vp get_p_pi();
        void set_p_pi(vp p_pi);
        vp get_n();
        void set_n(vp n);
};

#endif
