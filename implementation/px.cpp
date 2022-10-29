#include "../header/px.hpp"
#include <algorithm>

px::px(){ r = g = b = a = 1; }
px::px(double r, double g, double b,  double a): r(r), g(g), b(b), a(a){}

px px::operator+(px v){
    return px(this->get_r()+v.get_r(), this->get_g()+v.get_g(), this->get_b()+v.get_b(), std::min(this->get_a(), v.get_a()));
}

px px::operator*(double alp){ return px(alp*this->r, alp*this->g, alp*this->b, this->a); }
        
px px::operator*(px v){
    return px(this->get_r()*v.get_r(), this->get_g()*v.get_g(), this->get_b()*v.get_b(), this->get_a()*v.get_a());
}

px px::operator/(double alp){ return px(this->r/alp, this->g/alp, this->b/alp); }

// unsigned int px::convert_red(){ return std::min(r*((1<<BITS_RED_CHANNEL)-1), 255.0); }
unsigned int px::convert_red(){ return std::min(1.0, r)*((1<<BITS_RED_CHANNEL)-1); }
unsigned int px::convert_green(){ return std::min(1.0, g)*((1<<BITS_RED_CHANNEL)-1); }
unsigned int px::convert_blue(){ return std::min(1.0, b)*((1<<BITS_RED_CHANNEL)-1); }
unsigned int px::convert_alpha(){ return std::min(1.0, a)*((1<<BITS_RED_CHANNEL)-1); }

//Getters and Setters
double px::get_r(){ return this->r; }
void px::set_r(double r) { this->r = r; }
double px::get_g(){ return this->g; }
void px::set_g(double g) { this->g = g; }
double px::get_b(){ return this->b; }
void px::set_b(double b) { this->b = b; }
double px::get_a(){ return this->a; }
void px::set_a(double a) { this->a = a; }
