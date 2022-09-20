#include <cmath>
#include <iostream>
#include "../header/vp.hpp"

vp::vp() : x(0), y(0), z(0){}
vp::vp(double x, double y, double z) : x(x), y(y), z(z){}

vp vp::operator+(vp v){ 
    return vp(this->x+v.x, this->y+v.y, this->z+v.z);
}

vp vp::operator-(vp v){ 
    return vp(this->x-v.x, this->y-v.y, this->z-v.z);
}

vp vp::operator-(){
    return vp(-this->x, -this->y, -this->z);
}

double vp::operator*(vp v){
    return this->x*v.x + this->y*v.y + this->z*v.z;
}

vp vp::operator*(double alp){
    return vp(this->x*alp, this->y*alp, this->z*alp);
}

vp vp::operator/(double alp){
    return vp(this->x/alp, this->y/alp, this->z/alp);
}

double vp::operator~(){
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z); 
}

vp vp::operator%(vp v){
    return vp(
        this->get_y()*v.get_z() - this->get_z()*v.get_y(),
        this->get_z()*v.get_x() - this->get_x()*v.get_z(),
        this->get_x()*v.get_y() - this->get_y()*v.get_x()
    );
}

void vp::print(){
    std::cout << this->x << " " << this->y << " " << this->z << "\n";
}


//Getters and Setters
double vp::get_x(){ return this->x; }
void vp::set_x(double x){ this->x = x; }
double vp::get_y(){ return this->y; }
void vp::set_y(double y){ this->y = y; }
double vp::get_z(){ return this->z; }
void vp::set_z(double z){ this->z = z; }
