#include "../header/comparator.hpp"
#include "../header/cube.hpp"
#include "../header/matrix.hpp"

cube::cube(){}
cube::cube(px k_a, px k_d, px k_s, double s) : mesh(vp(0, 0, 0), k_a, k_d, k_s, s){
    this->width = this->length = this->heigth = 1;
        
    //Vertices
    this->vertices.push_back(new vertex(new vp(-0.5, -0.5, +0.5)));
    this->vertices.push_back(new vertex(new vp(+0.5, -0.5, +0.5)));
    this->vertices.push_back(new vertex(new vp(+0.5, +0.5, +0.5))); 
    this->vertices.push_back(new vertex(new vp(-0.5, +0.5, +0.5)));
    this->vertices.push_back(new vertex(new vp(-0.5, +0.5, -0.5)));
    this->vertices.push_back(new vertex(new vp(-0.5, -0.5, -0.5))); 
    this->vertices.push_back(new vertex(new vp(+0.5, -0.5, -0.5))); 
    this->vertices.push_back(new vertex(new vp(+0.5, +0.5, -0.5))); 
    //Faces 
    this->faces.push_back(new face(this->vertices[0], this->vertices[1], this->vertices[3]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[2], this->vertices[3]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[6], this->vertices[2]));
    this->faces.push_back(new face(this->vertices[2], this->vertices[6], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[5], this->vertices[7], this->vertices[6]));
    this->faces.push_back(new face(this->vertices[5], this->vertices[4], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[0], this->vertices[4], this->vertices[5]));
    this->faces.push_back(new face(this->vertices[3], this->vertices[4], this->vertices[0]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[2], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[3], this->vertices[2]));
    this->faces.push_back(new face(this->vertices[0], this->vertices[5], this->vertices[1]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[5], this->vertices[6]));
}

vp cube::get_def_point(){ return this->center; }
