#include "../header/point_light.hpp"

point_light::point_light(double intensity, vp position) : specular_light(intensity), position(position){}

double point_light::calculate_intensity(vp P, vp N, vp V, int s){ 
    double i = 0.0;
    vp L = this->get_position()-P;  
    double ndl = N*L;
    if(ndl > 0.0) i += (this->get_intensity()*ndl)/((~N)*(~L));
    i += specular(N, L, V, s);
    return i;
}

//Getters and Setters
vp point_light::get_position(){ return this->position; }
void point_light::set_position(vp position) { this->position = position; }
