#include "../header/object.hpp"

object::object(){}
object::object(px k_a, px k_d, px k_s, double specular) : k_a(k_a), k_d(k_d), k_s(k_s), specular(specular){}

//Getters and Setters
px object::get_k_a(){ return this->k_a; }
void object::set_k_a(px k_a){ this->k_a = k_a; }
px object::get_k_d(){ return this->k_d; }
void object::set_k_d(px k_d){ this->k_d = k_d; }
px object::get_k_s(){ return this->k_s; }
void object::set_k_s(px k_s){ this->k_s = k_s; }
double object::get_specular(){ return this->specular; }
void object::set_specular(double specular){ this->specular = specular; }
