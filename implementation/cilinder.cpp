#include <cmath>
#include "../header/cilinder.hpp"
#include "../header/plan.hpp"
#include "../header/matrix.hpp"
#include <bits/stdc++.h>

cilinder::cilinder(){}

cilinder::cilinder(vp center, vp direction, double r, double heigth, px k_a, px k_d, px k_s, double s) :
    center(center), direction((direction/(~direction))), radio(r), heigth(heigth), object(k_a, k_d, k_s, s){}

cilinder::cilinder(vp center, vp pa, vp pb, double r, px k_a, px k_d, px k_s, double s) : 
    center(center), direction((pb-pa)/(~(pb-pa))), heigth(~(pb-pa)), radio(r), object(k_a, k_d, k_s, s){}

bool cilinder::in_shell(vp P){
    double projection = ((P-this->get_center())*this->get_direction());
    return (projection > 0 && projection < this->get_heigth());
}

bool cilinder::in_base(vp P, vp p_pi, vp n){
    vp cp = P-p_pi;
    return ((~cp) <= this->get_radio());
    return (((cp*n) == 0.0) && ((~cp) <= this->get_radio()));
}

double cilinder::ray_intersect_base(vp O, vp D, vp p_pi, vp n){
    double t; plan p(p_pi, n);
    std::tie(t, t) = p.intersection_with_ray(O, D);
    vp P = (O + D*t);
    return (in_base(P, p_pi, n)) ? t : INF;
}

std::tuple<double, double> cilinder::ray_intersect_cylinder_shell_matrix(vp O, vp D){
    double t1 = INF, t2 = INF;
    //Auxiliar Matrizes
    matrix dc = matrix::vector_to_matrix(this->get_direction());
    matrix dr = matrix::vector_to_matrix(D);
    matrix w = matrix::vector_to_matrix(O-this->get_center());
    matrix M = matrix::identity(3) - (dc*(~dc));
    //Coeficients
    double a = ((~dr)*M*dr).matrix_to_scalar();
    if(a-EPS == 0.0) return {t1, t2};
    double b = ((~w)*M*dr).matrix_to_scalar()*2;
    double c = ((~w)*M*w).matrix_to_scalar()-(this->get_radio()*this->get_radio());
    //Second degree equation
    double DELTA = b*b - 4*a*c;
    if(DELTA+EPS < 0.0) return {t1, t2};
    t1 = (-b+sqrt(DELTA))/(2*a);
    t2 = (-b-sqrt(DELTA))/(2*a);
    //check if the points are in cylinder's shell
    vp P1 = O + D*t1;
    t1 = (in_shell(P1)) ? t1 : INF;
    vp P2 = O + D*t2;
    t2 = (in_shell(P2)) ? t2 : INF;
    return {t1, t2};
}


std::tuple<double, double> cilinder::ray_intersect_cylinder_shell_vector(vp O, vp D){
    double t1 = INF, t2 = INF;
    //Auxiliar vectors and numbers
    vp q = O-this->get_center();
    double alpha = this->get_direction()*D, beta = q*D, gamma = q*this->get_direction(), delta = q*q;
    //Coefficients
    double a = 1-alpha*alpha;
    if(a-EPS == 0.0) return {t1, t2};
    double b = beta - alpha*gamma;
    double c = delta - (gamma*gamma) - (this->get_radio(), this->get_radio());
    //Second degree equation
    double DELTA = b*b - 4*a*c;
    if(DELTA+EPS < 0.0) return {t1, t2};
    t1 = (-b+sqrt(DELTA))/(2*a);
    t2 = (-b-sqrt(DELTA))/(2*a);
    //check if the points are in cylinder's shell
    vp P1 = O + D*t1;
    t1 = (in_shell(P1)) ? t1 : INF;
    vp P2 = O + D*t2;
    t2 = (in_shell(P2)) ? t2 : INF;
    return {t1, t2};
}

std::tuple<double, double> cilinder::intersection_with_ray(vp O, vp D){
    std::vector<double> t; double aux1, aux2;
    //Check if there are intersection with the base of cilinder
    aux1 =  ray_intersect_base(O, D, this->get_center(), -this->get_direction());
    aux2 = ray_intersect_base(O, D, this->get_center() + this->get_direction()*this->get_heigth(), this->get_direction());
    t.emplace_back(aux1); t.emplace_back(aux2);
    //Check if there are intersection with the shell of cilinder
    // std::tie(aux1, aux2) = ray_intersect_cylinder_shell_vector(O, D); 
    std::tie(aux1, aux2) = ray_intersect_cylinder_shell_matrix(O, D); 
    t.emplace_back(aux1); t.emplace_back(aux2);
    //Sort vector in order to choose the minimum 't' valid
    sort(t.begin(), t.end());
    return {t[0], t[1]};
}

vp cilinder::normal(vp P){
    if(in_base(P, this->get_center(), -this->get_direction())) return -this->get_direction();
    if(in_base(P, this->get_center() + this->get_direction()*this->get_heigth(), this->get_direction())) return this->get_direction();
    vp cp = P-this->get_center();
    vp ap = cp - (this->get_direction()*(cp*this->get_direction()));
    ap = ap/~(ap);
    return ap;
}

//Getters and Setters
vp cilinder::get_center(){ return this->center; }
void cilinder::set_center(vp center){ this->center = center; }
vp cilinder::get_direction(){ return this->direction; }
void cilinder::set_direction(vp direction){ this->direction = direction; }
double cilinder::get_radio(){ return this->radio; }
void cilinder::set_radio(double radio){ this->radio = radio; }
double cilinder::get_heigth(){ return this->heigth; }
void cilinder::set_heigth(double heigth){ this->heigth = heigth; }
