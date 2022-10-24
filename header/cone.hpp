#ifndef CONE_HPP
#define CONE_HPP

#include "object.hpp"
#include "vp.hpp"
#include <tuple>

class cone : public object{
    private:
        vp center, direction; 
        double radio, heigth;
        bool has_base;
        
        bool in_shell(vp P);
        bool in_base(vp P, vp p_pi, vp n);
        std::tuple<double, double> ray_intersect_cone_shell_vector(vp O, vp D);
        double ray_intersect_base(vp O, vp D, vp p_pi, vp n);
        vp normal_with_shell(vp &O, vp &D, double &t);
     
    public:
        cone();
        cone(vp center, vp direction, double r, double heigth, px k_a, px k_d, px k_s, double s, bool has_base);
        cone(vp center, vp top, double r, px k_a, px k_d, px k_s, double s, bool has_base);
    
        std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);
    
        //transformations
        void transform();
    
        //Getters and Setters
        vp get_center();
        void set_center(vp center);
        vp get_direction();
        void set_direction(vp direction);
        double get_radio();
        void set_radio(double radio);
        double get_heigth();
        void set_heigth(double radio);
        bool get_has_base();
        void set_has_base(bool has_base);
};

#endif
