#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <tuple>
#include "vp.hpp"
#include "px.hpp"
#include "matrix.hpp"

class object{
    private:
        px k_a, k_d, k_s;   //intensity of ambient, difuse ans specular light_reflection
        double specular;    //object's shineness
    
    protected:
        std::vector<matrix> transformations; 
    
    public:
        object(); 
        object(px k_a, px k_d, px k_s, double specular);
        
        //return scalar 't' and normal with the point of intersection with the object
        virtual std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max) = 0;


        //transformations 
        void transform();
        void translation(vp P);
        void rotation_x(double angle);
        void rotation_y(double angle);
        void rotation_z(double angle);
        void shear_xy(double angle);
        void shear_yx(double angle);
        void shear_xz(double angle);
        void shear_zx(double angle);
        void shear_yz(double angle);
        void shear_zy(double angle);


        //Getters and Setters
        px get_k_a();
        void set_k_a(px k_a);
        px get_k_d();
        void set_k_d(px k_d);
        px get_k_s();
        void set_k_s(px k_s);
        double get_specular();
        void set_specular(double specular);
};

#endif
