#include <cmath>
#include "../header/sphere.hpp"

sphere::sphere(){}
sphere::sphere(vp center, double r, double s, px color) : center(center), radio(r), specular(s), color(color){}
sphere::sphere(double x, double y, double z, double r, double s, px color) : center(vp(x, y, z)), radio(r), specular(s), color(color){}

std::tuple<double, double> sphere::intersection_with_ray(vp O, vp D){
    vp CO = O - this->center;

    double a = D*D;
    double b = 2*(CO*D);
    double c = CO*CO - this->radio*this->radio;
    double delta = b*b - 4*a*c;
    
    if(delta < 0) return {INF, INF};        //there are no intessection
    double t1 = (-b + sqrt(delta))/(2*a);
    double t2 = (-b - sqrt(delta))/(2*a);

    return {t1, t2};
}

//Getters and Setters
vp sphere::get_center(){ return this->center; }
void sphere::set_center(vp center){ this->center = center; }
double sphere::get_radio(){ return this->radio; }
void sphere::set_radio(double radio){ this->radio = radio; }
double sphere::get_specular(){ return this->specular; }
void sphere::set_specular(double specular){ this->specular = specular; }
px sphere::get_color(){ return this->color; }
void sphere::set_color(px color){ this->color = color; }
