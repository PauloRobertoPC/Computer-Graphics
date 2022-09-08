#include "../header/direction_light.hpp"

direction_light::direction_light(double intensity, vp direction) : specular_light(intensity), direction(direction){}

double direction_light::calculate_intensity(vp P, vp N, vp V, int s){ 
    double i = 0.0;
    vp L = get_direction();  
    double ndl = N*L;
    if(ndl > 0.0) i += (this->get_intensity()*ndl)/((~N)*(~L));
    i += specular(N, L, V, s);
    return i;
}

//Getters and Setters
vp direction_light::get_direction(){ return this->direction; }
void direction_light::set_direction(vp direction) { this->direction = direction; }
