#include "../header/ambient_light.hpp"

ambient_light::ambient_light(double intensity) : light(intensity){} 

double ambient_light::calculate_intensity(vp P, vp N, vp V, int s){ 
    return this->get_intensity(); 
}
