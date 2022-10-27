#include "../header/ambient_light.hpp"

ambient_light::ambient_light(px intensity) : light(intensity){} 

px ambient_light::calculate_intensity(vp P, vp N, vp V, object* obj, bool calculate){ 
    return obj->get_k_a()*this->get_intensity(); 
}


void ambient_light::to_camera(matrix M){}

vp ambient_light::get_l(vp P){ return vp(0, 0, 0); }
