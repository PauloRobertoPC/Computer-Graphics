#include "../header/object.hpp"

object::object(){}
object::object(px k_a, px k_d, px k_s, double specular) : k_a(k_a), k_d(k_d), k_s(k_s), specular(specular){
    this->transformations = matrix::identity(4);
}

//transformations
void object::translation(vp P){
    vp t = P-this->get_def_point();
    matrix T = matrix::translation_matrix(t); 
    this->transformations = T*this->transformations; 
    this->transform();
}

void object::rotation_auxiliar(matrix M){
    vp T = this->get_def_point();  
    this->transformations = M*this->transformations; 
    this->transform();
    this->translation(T);
}
void object::rotation_x(double angle){ rotation_auxiliar(matrix::rotationX_matrix(angle)); }
void object::rotation_y(double angle){ rotation_auxiliar(matrix::rotationY_matrix(angle)); }
void object::rotation_z(double angle){ rotation_auxiliar(matrix::rotationZ_matrix(angle)); }
void object::rotate_arbitrary(vp o, vp direction, double angle){ rotation_auxiliar(matrix::rotation_arbitrary_matrix(o, direction, angle)); }

void object::shear_xy(double angle){}
void object::shear_yx(double angle){}
void object::shear_xz(double angle){}
void object::shear_zx(double angle){}
void object::shear_yz(double angle){}
void object::shear_zy(double angle){}

void object::mirror_xy(){ this->transformations = matrix::mirroringXY_matrix()*this->transformations; this->transform(); }
void object::mirror_xz(){ this->transformations = matrix::mirroringXZ_matrix()*this->transformations; this->transform(); } 
void object::mirror_yz(){ this->transformations = matrix::mirroringYZ_matrix()*this->transformations; this->transform(); }
void object::mirror_arbitrary(vp n, vp p){ this->transformations = matrix::mirror_arbitrary_matrix(n, p)*this->transformations; this->transform(); }

//Getters and Setters
px object::get_k_a(){ return this->k_a; }
void object::set_k_a(px k_a){ this->k_a = k_a; }
px object::get_k_d(){ return this->k_d; }
void object::set_k_d(px k_d){ this->k_d = k_d; }
px object::get_k_s(){ return this->k_s; }
void object::set_k_s(px k_s){ this->k_s = k_s; }
double object::get_specular(){ return this->specular; }
void object::set_specular(double specular){ this->specular = specular; }
