#include "../header/px.hpp"
#include <algorithm>

px::px(){ r = g = b = 1; } //Standard Color(White)
px::px(double r, double g, double b): r(std::min(r, 1.0)), g(std::min(g, 1.0)), b(std::min(b, 1.0)){}

px px::operator*(double alp){ return px(alp*this->r, alp*this->g, alp*this->b); }

unsigned int px::convert_red(){ return r*((1<<BITS_RED_CHANNEL)-1); }
unsigned int px::convert_green(){ return g*((1<<BITS_GREEN_CHANNEL)-1); }
unsigned int px::convert_blue(){ return b*((1<<BITS_BLUE_CHANNEL)-1); }

//Getters and Setters
double px::get_r(){ return this->r; }
void px::set_r(double r) { this->r = r; }
double px::get_g(){ return this->g; }
void px::set_g(double g) { this->g = g; }
double px::get_b(){ return this->b; }
void px::set_b(double b) { this->b = b; }
