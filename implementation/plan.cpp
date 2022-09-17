#include "../header/plan.hpp"

plan::plan(){}
plan::plan(vp p_pi, vp n) : p_pi(p_pi), n(n), object(){}
plan::plan(vp p_pi, vp n, px k_a, px k_d, px k_s, double s) : p_pi(p_pi), n(n), object(k_a, k_d, k_s, s){}

std::tuple<double, vp> plan::intersection_with_ray(vp O, vp D, double t_min, double t_max){
    double denominator = D*this->get_n();
    if(denominator == 0.0) return {INF, vp()};
    double numerator = (O-this->get_p_pi())*this->get_n();
    double t = -(numerator/denominator);
    return {t, this->get_n()};
}

//Getters and Setters
vp plan::get_p_pi(){ return this->p_pi; }
void plan::set_p_pi(vp p_pi){ this->p_pi = p_pi; }
vp plan::get_n(){ return this->n; }
void plan::set_n(vp n){ this->n = n; }
