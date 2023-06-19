#include "../../header/world/viewport.hpp"
#include <cmath>

viewport::viewport(double h, double w, double d, canvas &c, sampler *sp) : h(h), w(w), d(d), c(c), sp(sp){
    change_dx_dy();
}

point_2D viewport::sample_square(){
    point_2D s = sp->sample_unit_square();
    s.x = std::lerp(-dx, dx, s.x); // linear interpolation to put the value between [0, 1] to [-dx, dx]
    s.y = std::lerp(-dy, dy, s.y);
    return s;
}

void viewport::change_dx_dy(){
    this->dx = 1.0 * w / c.get_m();
    this->dy = 1.0 * h / c.get_n();
}

int viewport::qnt_samples(){
    return sp->get_num_samples();
}

//Getters and Setters
double viewport::get_h(){ return this->h; }
void viewport::set_h(double h){ this->h = h; }
double viewport::get_w(){ return this->w; }
void viewport::set_w(double w){ this->w = w; }
double viewport::get_d(){ return this->d; }
void viewport::set_d(double d){ this->d = d; }
double viewport::get_dx(){ return this->dx; }
double viewport::get_dy(){ return this->dy; }

void viewport::set_wh(double w, double h){
    set_w(w);
    set_h(h);
    change_dx_dy();
}
