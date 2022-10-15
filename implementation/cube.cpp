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
        
    
    // //Vertices
    // this->vertices.push_back(new vertex(new vp(0.5, 0.5, 0.5))); 
    // this->vertices.push_back(new vertex(new vp(-0.5, 0.5, 0.5))); 
    // this->vertices.push_back(new vertex(new vp(-0.5, -0.5, 0.5))); 
    // this->vertices.push_back(new vertex(new vp(0.5, -0.5, 0.5))); 
    // this->vertices.push_back(new vertex(new vp(0.5, 0.5, -0.5))); 
    // this->vertices.push_back(new vertex(new vp(-0.5, 0.5, -0.5))); 
    // this->vertices.push_back(new vertex(new vp(-0.5, -0.5,-0.5))); 
    // this->vertices.push_back(new vertex(new vp(0.5, -0.5, -0.5))); 
    // //Faces 
    // this->faces.push_back(new face(this->vertices[0], this->vertices[1], this->vertices[2]));
    // this->faces.push_back(new face(this->vertices[0], this->vertices[2], this->vertices[3]));
    // this->faces.push_back(new face(this->vertices[4], this->vertices[0], this->vertices[3]));
    // this->faces.push_back(new face(this->vertices[4], this->vertices[3], this->vertices[7]));
    // this->faces.push_back(new face(this->vertices[5], this->vertices[4], this->vertices[7]));
    // this->faces.push_back(new face(this->vertices[5], this->vertices[7], this->vertices[6]));
    // this->faces.push_back(new face(this->vertices[1], this->vertices[5], this->vertices[6]));
    // this->faces.push_back(new face(this->vertices[1], this->vertices[6], this->vertices[2]));
    // this->faces.push_back(new face(this->vertices[4], this->vertices[5], this->vertices[1]));
    // this->faces.push_back(new face(this->vertices[4], this->vertices[1], this->vertices[0]));
    // this->faces.push_back(new face(this->vertices[2], this->vertices[6], this->vertices[7]));
    // this->faces.push_back(new face(this->vertices[2], this->vertices[7], this->vertices[3]));
    
}

void cube::transform(){
    matrix M = matrix::identity(4);
    for(matrix m:this->transformations) M = M*m; 
    
    this->center = (M*matrix::vp_to_matrix(this->center)).matrix_to_vp();
    
    for(vertex* v:this->vertices){
        vp p = (M*matrix::vp_to_matrix(*v->get_pos())).matrix_to_vp();
        v->get_pos()->set_x(p.get_x());
        v->get_pos()->set_y(p.get_y());
        v->get_pos()->set_z(p.get_z());
    }

    for(face* f:this->faces){
        vp normal = ((*f->get_b()->get_pos())-(*f->get_a()->get_pos()))%((*f->get_c()->get_pos())-(*f->get_a()->get_pos()));
        if(comparator::neq(~(normal), 0.0)) normal = normal/~(normal);
        f->set_normal(normal);
    }

    transformations.clear();
}

void cube::translation(vp P){
    vp t = P-this->center;
    matrix T = matrix::translation_matrix(t); 
    transformations.emplace_back(T); 
}

void cube::rotation_x(double angle){ transformations.emplace_back(matrix::rotationX_matrix(angle)); }
void cube::rotation_y(double angle){ transformations.emplace_back(matrix::rotationY_matrix(angle)); }
void cube::rotation_z(double angle){ transformations.emplace_back(matrix::rotationZ_matrix(angle)); }
void cube::scaling(vp S){ transformations.emplace_back(matrix::scaling_matrix(S)); }
void cube::shear_xy(double angle){ transformations.emplace_back(matrix::shear_xy(angle)); }
void cube::shear_yx(double angle){ transformations.emplace_back(matrix::shear_yx(angle)); }
void cube::shear_xz(double angle){ transformations.emplace_back(matrix::shear_xz(angle)); }
void cube::shear_zx(double angle){ transformations.emplace_back(matrix::shear_zx(angle)); }
void cube::shear_yz(double angle){ transformations.emplace_back(matrix::shear_yz(angle)); }
void cube::shear_zy(double angle){ transformations.emplace_back(matrix::shear_zy(angle)); }
void cube::mirror_xy(){ transformations.emplace_back(matrix::mirroringXY_matrix()); }
void cube::mirror_xz(){ transformations.emplace_back(matrix::mirroringXZ_matrix()); }
void cube::mirror_yz(){ transformations.emplace_back(matrix::mirroringYZ_matrix()); }
