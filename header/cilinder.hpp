#ifndef CILINDER_HPP
#define CILINDER_HPP

#include "object.hpp"
#include "vp.hpp"
#include <tuple>

class cilinder : public object{
    private:
        vp center, direction; 
        double radio, heigth;
        
        bool in_shell(vp P);
        bool in_base(vp P, vp p_pi, vp n);
        std::tuple<double, double> ray_intersect_cylinder_shell_matrix(vp O, vp D);
        std::tuple<double, double> ray_intersect_cylinder_shell_vector(vp O, vp D);
        double ray_intersect_base(vp O, vp D, vp p_pi, vp n);
     
    public:
        cilinder();
        cilinder(vp center, vp direction, double r, double heigth, px k_a, px k_d, px k_s, double s);
        cilinder(vp center, vp pa, vp pb, double r, px k_a, px k_d, px k_s, double s);

        //calculate the intersections between the cilinder and the ray
        std::tuple<double, double> intersection_with_ray(vp O, vp D);
    
        vp normal(vp P);
    
        //Getters and Setters
        vp get_center();
        void set_center(vp center);
        vp get_direction();
        void set_direction(vp direction);
        double get_radio();
        void set_radio(double radio);
        double get_heigth();
        void set_heigth(double radio);
};

#endif
