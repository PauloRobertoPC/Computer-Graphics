#include "../header/plan.hpp"

plan::plan(){}
plan::plan(vp p_pi, vp n, double s, px color) : p_pi(p_pi), n(n), object(color, s){}

//calculate the intersections between the plan and the ray
std::tuple<double, double> plan::intersection_with_ray(vp O, vp D){
    double denominator = D*this->get_n();
    if(denominator == 0.0) return {INF, INF};
    double numerator = (O-this->get_p_pi())*this->get_n();
    double t = -(numerator/denominator);
    return {t, t};
}

vp plan::normal(vp P){
    return this->get_n();
}

//Getters and Setters
vp plan::get_p_pi(){ return this->p_pi; }
void plan::set_p_pi(vp p_pi){ this->p_pi = p_pi; }
vp plan::get_n(){ return this->n; }
void plan::set_n(vp n){ this->n = n; }
