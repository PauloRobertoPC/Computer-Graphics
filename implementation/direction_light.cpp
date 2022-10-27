#include "../header/direction_light.hpp"

direction_light::direction_light(px intensity, vp direction) : specular_light(intensity), direction(direction){}

px direction_light::calculate_intensity(vp P, vp N, vp V, object* obj, bool calculate){ 
    px i(0, 0, 0);
    if(!calculate) return i;
    vp L = get_direction();  
    double ndl = N*L;
    if(ndl > 0.0) i = i + (obj->get_k_d()*(this->get_intensity()*ndl)/((~N)*(~L)));
    i = i + specular(N, L, V, obj);
    return i;
}

vp direction_light::get_l(vp P){ return -get_direction(); }

void direction_light::to_camera(matrix M){
    this->direction = (M*matrix::vp_to_matrix(this->direction)).matrix_to_vp();
}

//Getters and Setters
vp direction_light::get_direction(){ return this->direction; }
void direction_light::set_direction(vp direction) { this->direction = direction; }
