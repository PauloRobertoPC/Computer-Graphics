#include "../header/camera.hpp"

camera::camera(vp E, vp look_at, vp up) : E(E) {
    vp vup = up - E;
    vp k = (E-look_at)/(~(E-look_at));
    vp i = vup % k; i = i/(~i);
    vp j = k % i;
    this->w2c = matrix::new_coordinates_inverse_matrix(i, j, k, E);
    this->c2w = matrix::new_coordinates_matrix(i, j, k, E);
}

vp camera::world_to_camera(vp p){
    return (this->w2c*matrix::vp_to_matrix(p)).matrix_to_vp();
}

vp camera::camera_to_world(vp p){
    return (this->c2w*matrix::vp_to_matrix(p)).matrix_to_vp();
}

vp camera::get_E(){ return this->E; }
matrix camera::get_w2c(){ return this->w2c; };
matrix camera::get_c2w(){ return this->c2w; };
