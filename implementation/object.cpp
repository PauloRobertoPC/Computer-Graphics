#include "../header/object.hpp"

object::object(){}
object::object(px color, double specular) : color(color), specular(specular){}

//Getters and Setters
px object::get_color(){ return this->color; }
void object::set_color(px color){ this->color = color; }
double object::get_specular(){ return this->specular; }
void object::set_specular(double specular){ this->specular = specular; }
