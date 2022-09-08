#include <cmath>
#include "../header/specular_light.hpp"

specular_light::specular_light(double intensity) : light(intensity){}

double specular_light::specular(vp N, vp L, vp V, int s){
    if(s != -1){
        vp R = (N*(N*L))*2 - L;
        double rdv = R*V;
        if(rdv > 0.0) return (this->get_intensity()*pow((rdv/((~R)*(~V))), s));
    }
    return 0.0;
}
