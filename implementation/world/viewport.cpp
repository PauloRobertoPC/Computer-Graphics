#include "../../header/world/viewport.hpp"

viewport::viewport(){ h = w = d = 0; }
viewport::viewport(double h, double w, double d) : h(h), w(w), d(d){}

//Getters and Setters
double viewport::get_h(){ return this->h; }
void viewport::set_h(double h){ this->h = h; }
double viewport::get_w(){ return this->w; }
void viewport::set_w(double w){ this->w = w; }
double viewport::get_d(){ return this->d; }
void viewport::set_d(double d){ this->d = d; }
