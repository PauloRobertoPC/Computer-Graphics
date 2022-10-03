#include "../header/cube.hpp"

cube::cube(){}
cube::cube(vp center, double a, px k_a, px k_d, px k_s, double s) : a(a), mesh(center, k_a, k_d, k_s, s){
    a /= 2;
    //Vertices
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(1), center.get_y()+a*(1), center.get_z()+a*(1)))); 
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(-1), center.get_y()+a*(1), center.get_z()+a*(1)))); 
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(-1), center.get_y()+a*(-1), center.get_z()+a*(1)))); 
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(1), center.get_y()+a*(-1), center.get_z()+a*(1)))); 
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(1), center.get_y()+a*(1), center.get_z()+a*(-1)))); 
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(-1), center.get_y()+a*(1), center.get_z()+a*(-1)))); 
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(-1), center.get_y()+a*(-1), center.get_z()+a*(-1)))); 
    this->vertices.push_back(new vertex(new vp(center.get_x()+a*(1), center.get_y()+a*(-1), center.get_z()+a*(-1)))); 
    //Faces 
    this->faces.push_back(new face(this->vertices[0], this->vertices[1], this->vertices[2]));
    this->faces.push_back(new face(this->vertices[0], this->vertices[2], this->vertices[3]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[0], this->vertices[3]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[3], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[5], this->vertices[4], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[5], this->vertices[7], this->vertices[6]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[5], this->vertices[6]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[6], this->vertices[2]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[5], this->vertices[1]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[1], this->vertices[0]));
    this->faces.push_back(new face(this->vertices[2], this->vertices[6], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[2], this->vertices[7], this->vertices[3]));
    
    // this->vertices.push_back(new vertex(new vp(center.get_x()+a*(-1), center.get_y()+a*(-1), center.get_z()+a*(1)))); 
    // this->vertices.push_back(new vertex(new vp(center.get_x()+a*(1), center.get_y()+a*(-1), center.get_z()+a*(1)))); 
    // this->vertices.push_back(new vertex(new vp(center.get_x()+a*(-1), center.get_y()+a*(1), center.get_z()+a*(1)))); 
    // this->faces.push_back(new face(this->vertices[0], this->vertices[1], this->vertices[2]));
    
    a *= 2;
}

double cube::get_a(){ return this->a; }
void cube::set_a(double a){ this->a = a; }
