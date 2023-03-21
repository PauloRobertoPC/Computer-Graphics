#include <cmath>
#include "../header/sphere.hpp"
#include "../header/comparator.hpp"

sphere::sphere() {}
sphere::sphere(vp center, double r, px k_a, px k_d, px k_s, double s, double reflective) : center(center), radio(r), object(k_a, k_d, k_s, s, reflective) {}

vp sphere::get_def_point() { return this->center; }

std::tuple<double, vp> sphere::intersection_with_ray(vp O, vp D, double t_min, double t_max)
{
    double t = INF;
    vp n;
    vp CO = O - this->center;

    double a = D * D;
    double b = 2 * (CO * D);
    double c = CO * CO - this->radio * this->radio;
    double delta = b * b - 4 * a * c;

    if (delta < 0)
        return {INF, vp()}; // there are no intessection
    double t1 = (-b + sqrt(delta)) / (2 * a);
    double t2 = (-b - sqrt(delta)) / (2 * a);

    // if(t1-EPS > t_min && t1 < t_max && t1 < t) t = t1, n = normal_with_shell(O, D, t1);
    // if(t2-EPS > t_min && t2 < t_max && t2 < t) t = t2, n = normal_with_shell(O, D, t2);
    if (comparator::g(t1, t_min) && comparator::l(t1, t_max) && comparator::l(t1, t))
        t = t1, n = normal_with_shell(O, D, t1);
    if (comparator::g(t2, t_min) && comparator::l(t2, t_max) && comparator::l(t2, t))
        t = t2, n = normal_with_shell(O, D, t2);
    return {t, n};
}

vp sphere::normal_with_shell(vp &O, vp &D, double &t)
{
    vp P = O + D * t;
    return (P - this->get_center()) / this->get_radio();
}

// transformations
void sphere::to_camera(matrix M)
{
    this->center = (M * matrix::vp_to_matrix(this->center)).matrix_to_vp();
}

void sphere::transform()
{
    this->center = (this->transformations * matrix::vp_to_matrix(this->center)).matrix_to_vp();
    transformations = matrix::identity(4);
}

void sphere::scaling(vp S)
{
    this->radio = S.get_x();
}

// Getters and Setters
vp sphere::get_center() { return this->center; }
void sphere::set_center(vp center) { this->center = center; }
double sphere::get_radio() { return this->radio; }
void sphere::set_radio(double radio) { this->radio = radio; }
