#include "../header/plan.hpp"

plan::plan() {}
plan::plan(vp p_pi, vp n) : p_pi(p_pi), n(n), object() {}
plan::plan(vp p_pi, vp n, px k_a, px k_d, px k_s, double s, double reflective) : p_pi(p_pi), n(n), object(k_a, k_d, k_s, s, reflective) {}
plan::plan(vp p_pi, vp n, const char *name, double s, double reflective) : p_pi(p_pi), n(n), object(name, s, reflective) {}

vp plan::get_def_point() { return this->p_pi; }

std::tuple<double, vp> plan::intersection_with_ray(vp O, vp D, double t_min, double t_max)
{
    double denominator = D * this->get_n();
    if (denominator == 0.0)
        return {INF, vp()};
    double numerator = (O - this->get_p_pi()) * this->get_n();
    double t = -(numerator / denominator);
    return {t, this->get_n()};
}

// transformations
void plan::to_camera(matrix M)
{
    this->p_pi = (M * matrix::vp_to_matrix(this->p_pi)).matrix_to_vp();
    this->n = (M * matrix::vp_to_matrix(this->n, 0)).matrix_to_vp();
    this->n = this->n / ~this->n;
}

void plan::transform()
{
    this->p_pi = (this->transformations * matrix::vp_to_matrix(this->p_pi)).matrix_to_vp();
    transformations = matrix::identity(4);
}

void plan::translation(vp P, bool point) {}
void plan::rotation_x(double angle) {}
void plan::rotation_y(double angle) {}
void plan::rotation_z(double angle) {}
void plan::rotate_arbitrary(vp o, vp direction, double angle) {}
void plan::scaling(vp S) {}
void plan::shear_xy(double angle) {}
void plan::shear_yx(double angle) {}
void plan::shear_xz(double angle) {}
void plan::shear_zx(double angle) {}
void plan::shear_yz(double angle) {}
void plan::shear_zy(double angle) {}
void plan::mirror_xy() {}
void plan::mirror_xz() {}
void plan::mirror_yz() {}
void plan::mirror_arbitrary(vp n, vp p) {}

// Getters and Setters
vp plan::get_p_pi() { return this->p_pi; }
void plan::set_p_pi(vp p_pi) { this->p_pi = p_pi; }
vp plan::get_n() { return this->n; }
void plan::set_n(vp n) { this->n = n; }
