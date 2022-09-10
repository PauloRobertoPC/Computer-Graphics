#include <cmath>
#include "../header/light.hpp"

light::light(px intensity) : intensity(intensity){}

//Getters and Setters
px light::get_intensity(){ return intensity; }
void light::set_intensity(px intensity){ this->intensity = intensity; }
