#include "../header/point_light.hpp"

point_light::point_light(px intensity, vp position) : specular_light(intensity), position(position){}

px point_light::calculate_intensity(vp P, vp N, vp V, object* obj, bool calculate){ 
    px i(0, 0, 0);
    if(!calculate) return i;
    vp L = this->get_position()-P;  
    double ndl = N*L;
    if(ndl > 0.0) i = i + (obj->get_k_d()*(this->get_intensity()*ndl)/((~N)*(~L)));
    i = i + specular(N, L, V, obj);
    return i;
}

vp point_light::get_l(vp P){
    return this->get_position()-P;
}

//Getters and Setters
vp point_light::get_position(){ return this->position; }
void point_light::set_position(vp position) { this->position = position; }
