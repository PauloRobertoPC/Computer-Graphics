#include <cmath>
#include "../header/light.hpp"

light::light(double intensity) : intensity(intensity){}

double light::specular(vp N, vp L, vp V, int s){
    if(s != -1){
        vp R = (N*(N*L))*2 - L;
        double rdv = R*V;
        if(rdv > 0.0) return (this->get_intensity()*pow((rdv/((~R)*(~V))), s));
    }
    return 0.0;
}

//Getters and Setters
double light::get_intensity(){ return intensity; }
void light::set_intensity(double intensity){ this->intensity = intensity; }
