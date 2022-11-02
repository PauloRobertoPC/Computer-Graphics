#include <bits/stdc++.h>
#include "../header/spot_light.hpp"
#include "../header/comparator.hpp"

spot_light::spot_light(px intensity, vp position, vp direction, double angle) : specular_light(intensity), position(position), direction(direction/(~direction)), angle(angle) {}

px spot_light::calculate_intensity(vp P, vp N, vp V, object* obj, bool calculate){ 
    px i(0, 0, 0);
    if(!calculate) return i;
    vp L = this->get_position()-P;  
    L = L/(~L);
    double fator = -(L*this->get_direction());
    if(comparator::l(fator, cos(angle))) return i;
    double ndl = N*L;
    if(ndl > 0.0) i = i + (obj->get_k_d()*(this->get_intensity()*ndl))*fator;
    i = i + specular(N, L, V, obj)*fator;
    return i;
}

vp spot_light::get_l(vp P){
    return this->get_position()-P;
}

void spot_light::to_camera(matrix M){
    this->position = (M*matrix::vp_to_matrix(this->position)).matrix_to_vp();
    this->direction = (M*matrix::vp_to_matrix(this->direction, 0)).matrix_to_vp();
    this->direction = this->direction/~this->direction;
}

//Getters and Setters
vp spot_light::get_position(){ return this->position; }
void spot_light::set_position(vp position) { this->position = position; }
vp spot_light::get_direction(){ return this->direction; }
void spot_light::set_direction(vp direction){ this->direction = direction; }
