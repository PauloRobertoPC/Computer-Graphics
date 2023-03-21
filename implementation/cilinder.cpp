#include <cmath>
#include "../header/cilinder.hpp"
#include "../header/plan.hpp"
#include "../header/matrix.hpp"
#include "../header/comparator.hpp"
#include <bits/stdc++.h>

cilinder::cilinder() {}

cilinder::cilinder(vp center, vp direction, double r, double heigth, px k_a, px k_d, px k_s, double s, double reflective, bool has_base, bool has_top) : center(center), direction((direction / (~direction))), radio(r), heigth(heigth), object(k_a, k_d, k_s, s, reflective), has_base(has_base), has_top(has_top)
{
    direction = direction / ~direction;
    this->top = center + direction * heigth;
}

cilinder::cilinder(vp center, vp top, double r, px k_a, px k_d, px k_s, double s, double reflective, bool has_base, bool has_top) : center(center), direction((top - center) / (~(top - center))), heigth(~(top - center)), radio(r), object(k_a, k_d, k_s, s, reflective), has_base(has_base), has_top(has_top), top(top) {}

vp cilinder::get_def_point() { return this->center; }

bool cilinder::in_shell(vp P)
{
    double projection = ((P - this->get_center()) * this->get_direction());
    return (projection > 0 && projection < this->get_heigth());
}

bool cilinder::in_base(vp P, vp p_pi, vp n)
{
    vp cp = P - p_pi;
    double cp_x_n = cp * n;
    // bool is_zero = (cp_x_n+EPS > 0.0) && (cp_x_n-EPS < 0.0);
    // bool in_radio = ((~cp) <= this->get_radio());
    bool is_zero = comparator::eq(cp_x_n, 0.0);
    bool in_radio = comparator::leq(~cp, this->get_radio());
    return (in_radio && is_zero);
}

double cilinder::ray_intersect_base(vp O, vp D, vp p_pi, vp n)
{
    double t;
    vp aux;
    plan p(p_pi, n);
    std::tie(t, aux) = p.intersection_with_ray(O, D, -1, -1);
    vp P = (O + D * t);
    return (in_base(P, p_pi, n)) ? t : INF;
}

std::tuple<double, double> cilinder::ray_intersect_cylinder_shell_vector(vp O, vp D)
{
    double t1 = INF, t2 = INF;
    // Auxiliar vectors and numbers
    vp v = (O - this->get_center()) - this->get_direction() * ((O - this->get_center()) * this->get_direction());
    vp w = D - this->get_direction() * (D * this->get_direction());
    double a = w * w;
    double b = v * w * 2;
    double c = v * v - this->get_radio() * this->get_radio();
    // Second degree equation
    double DELTA = b * b - 4 * a * c;
    // if(DELTA+EPS < 0.0) return {t1, t2};
    if (comparator::l(DELTA, 0.0))
        return {t1, t2};
    t1 = (-b + sqrt(DELTA)) / (2 * a);
    t2 = (-b - sqrt(DELTA)) / (2 * a);
    // check if the points are in cylinder's shell
    vp P1 = O + D * t1;
    t1 = (in_shell(P1)) ? t1 : INF;
    vp P2 = O + D * t2;
    t2 = (in_shell(P2)) ? t2 : INF;
    return {t1, t2};
}

std::tuple<double, vp> cilinder::intersection_with_ray(vp O, vp D, double t_min, double t_max)
{
    double aux1 = INF, aux2 = INF, t = INF;
    vp n;
    // Check if there are intersection with the base of cilinder
    aux1 = ray_intersect_base(O, D, this->get_center(), -this->get_direction());
    aux2 = ray_intersect_base(O, D, this->get_center() + this->get_direction() * this->get_heigth(), this->get_direction());
    // if(aux1-EPS > t_min && aux1 < t_max && aux1 < t){
    if (this->get_has_base() && comparator::g(aux1, t_min) && comparator::l(aux1, t_max) && comparator::l(aux1, t))
        t = aux1, n = -this->get_direction();
    // if(aux2-EPS > t_min && aux2 < t_max && aux2 < t){
    if (this->get_has_top() && comparator::g(aux2, t_min) && comparator::l(aux2, t_max) && comparator::l(aux2, t))
        t = aux2, n = this->get_direction();
    // Check if there are intersection with the shell of cilinder
    std::tie(aux1, aux2) = ray_intersect_cylinder_shell_vector(O, D);
    // if(aux1-EPS > t_min && aux1 < t_max && aux1 < t) t = aux1, n = normal_with_shell(O, D, aux1);
    // if(aux2-EPS > t_min && aux2 < t_max && aux2 < t) t = aux2, n = normal_with_shell(O, D, aux2);
    if (comparator::g(aux1, t_min) && comparator::l(aux1, t_max) && comparator::l(aux1, t))
        t = aux1, n = normal_with_shell(O, D, aux1);
    if (comparator::g(aux2, t_min) && comparator::l(aux2, t_max) && comparator::l(aux2, t))
        t = aux2, n = normal_with_shell(O, D, aux2);
    return {t, n};
}

vp cilinder::normal_with_shell(vp &O, vp &D, double &t)
{
    vp P = O + D * t;
    vp cp = P - this->get_center();
    vp ap = cp - (this->get_direction() * (cp * this->get_direction()));
    ap = ap / ~(ap);
    return ap;
}

// transformations
void cilinder::transform()
{
    this->center = (this->transformations * matrix::vp_to_matrix(this->center)).matrix_to_vp();
    this->top = (this->transformations * matrix::vp_to_matrix(this->top)).matrix_to_vp();
    this->direction = (top - center) / ~(top - center);
    transformations = matrix::identity(4);
}

void cilinder::to_camera(matrix M)
{
    this->center = (M * matrix::vp_to_matrix(this->center)).matrix_to_vp();
    this->top = (M * matrix::vp_to_matrix(this->top)).matrix_to_vp();
    this->direction = (M * matrix::vp_to_matrix(this->direction, 0)).matrix_to_vp();
    this->direction = this->direction / ~this->direction;
}

void cilinder::scaling(vp S)
{
    this->radio = S.get_x();
    this->heigth = S.get_y();
    this->top = this->center + this->direction * this->heigth;
}

// Getters and Setters
vp cilinder::get_center() { return this->center; }
void cilinder::set_center(vp center) { this->center = center; }
vp cilinder::get_direction() { return this->direction; }
void cilinder::set_direction(vp direction) { this->direction = direction; }
double cilinder::get_radio() { return this->radio; }
void cilinder::set_radio(double radio) { this->radio = radio; }
double cilinder::get_heigth() { return this->heigth; }
void cilinder::set_heigth(double heigth) { this->heigth = heigth; }
bool cilinder::get_has_base() { return this->has_base; }
void cilinder::set_has_base(bool has_base) { this->has_base = has_base; }
bool cilinder::get_has_top() { return this->has_top; }
void cilinder::set_has_top(bool has_top) { this->has_top = has_top; }
