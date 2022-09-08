#include <cmath>
#include "../header/light.hpp"

light::light(double intensity) : intensity(intensity){}

//Getters and Setters
double light::get_intensity(){ return intensity; }
void light::set_intensity(double intensity){ this->intensity = intensity; }
