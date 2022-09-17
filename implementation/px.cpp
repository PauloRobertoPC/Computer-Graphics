#include "../header/px.hpp"
#include <algorithm>

px::px(){ r = g = b = 1; } //Standard Color(White)
px::px(double r, double g, double b): r(std::min(r, 10000.0)), g(std::min(g, 10000.0)), b(std::min(b, 100.0)){}
//TODO: decide how to limitate the pixels in above constructor 
px px::operator+(px v){
    return px(this->get_r()+v.get_r(), this->get_g()+v.get_g(), this->get_b()+v.get_b());
}

px px::operator*(double alp){ return px(alp*this->r, alp*this->g, alp*this->b); }
        
px px::operator*(px v){
    return px(this->get_r()*v.get_r(), this->get_g()*v.get_g(), this->get_b()*v.get_b());
}

px px::operator/(double alp){ return px(this->r/alp, this->g/alp, this->b/alp); }

unsigned int px::convert_red(){ return std::min(r*((1<<BITS_RED_CHANNEL)-1), 255.0); }
unsigned int px::convert_green(){ return std::min(g*((1<<BITS_GREEN_CHANNEL)-1), 255.0); }
unsigned int px::convert_blue(){ return std::min(b*((1<<BITS_BLUE_CHANNEL)-1), 255.0); }

//Getters and Setters
double px::get_r(){ return this->r; }
void px::set_r(double r) { this->r = r; }
double px::get_g(){ return this->g; }
void px::set_g(double g) { this->g = g; }
double px::get_b(){ return this->b; }
void px::set_b(double b) { this->b = b; }
