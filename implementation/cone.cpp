#include <cmath>
#include "../header/cone.hpp"
#include "../header/plan.hpp"
#include "../header/comparator.hpp"
#include <bits/stdc++.h>

cone::cone() {}

cone::cone(vp center, vp direction, double r, double heigth, px k_a, px k_d, px k_s, double s, double reflective, bool has_base) : center(center), direction((direction / (~direction))), radio(r), heigth(heigth), object(k_a, k_d, k_s, s, reflective), has_base(has_base)
{
    direction = direction / ~direction;
    this->top = center + direction * heigth;
}

cone::cone(vp center, vp top, double r, px k_a, px k_d, px k_s, double s, double reflective, bool has_base) : center(center), direction((top - center) / (~(top - center))), heigth(~(top - center)), radio(r), object(k_a, k_d, k_s, s, reflective), has_base(has_base), top(top) {}

vp cone::get_def_point() { return this->center; }

bool cone::in_shell(vp P)
{
    double projection = ((P - this->get_center()) * this->get_direction());
    return (projection > 0 && projection <= this->get_heigth());
}

bool cone::in_base(vp P, vp p_pi, vp n)
{
    vp cp = P - p_pi;
    double cp_x_n = cp * n;
    // bool is_zero = (cp_x_n+EPS > 0.0) && (cp_x_n-EPS < 0.0);
    // bool in_radio = ((~cp) <= this->get_radio());
    bool is_zero = comparator::eq(cp_x_n, 0.0);
    bool in_radio = comparator::leq(~cp, this->get_radio());
    return (in_radio && is_zero);
}

double cone::ray_intersect_base(vp O, vp D, vp p_pi, vp n)
{
    double t;
    vp aux;
    plan p(p_pi, n);
    std::tie(t, aux) = p.intersection_with_ray(O, D, -1, -1);
    vp P = (O + D * t);
    return (in_base(P, p_pi, n)) ? t : INF;
}

std::tuple<double, double> cone::ray_intersect_cone_shell_vector(vp O, vp D)
{
    double t1 = INF, t2 = INF;
    // Auxiliar vectors and numbers
    vp V = this->get_center() + (this->get_direction() * this->get_heigth());
    vp v = V - O;
    double cos2 = (this->get_heigth() * this->get_heigth()) / (this->get_radio() * this->get_radio() + this->get_heigth() * this->get_heigth());
    double a = (D * this->get_direction()) * (D * this->get_direction()) - (D * D) * cos2;
    double b = ((v * D) * cos2 - (v * this->get_direction()) * (D * this->get_direction())) * 2;
    double c = (v * this->get_direction()) * (v * this->get_direction()) - (v * v) * cos2;
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

std::tuple<double, vp> cone::intersection_with_ray(vp O, vp D, double t_min, double t_max)
{
    double aux1 = INF, aux2 = INF, t = INF;
    vp n;
    // Check if there are intersection with the shell of cone
    std::tie(aux1, aux2) = ray_intersect_cone_shell_vector(O, D);
    // if(aux1-EPS > t_min && aux1 < t_max && aux1 < t) t = aux1, n = normal_with_shell(O, D, aux1);
    // if(aux2-EPS > t_min && aux2 < t_max && aux2 < t) t = aux2, n = normal_with_shell(O, D, aux2);
    if (comparator::g(aux1, t_min) && comparator::l(aux1, t_max) && comparator::l(aux1, t))
        t = aux1, n = normal_with_shell(O, D, aux1);
    if (comparator::g(aux2, t_min) && comparator::l(aux2, t_max) && comparator::l(aux2, t))
        t = aux2, n = normal_with_shell(O, D, aux2);
    // Check if there are intersection with the base of cone
    aux1 = ray_intersect_base(O, D, this->get_center(), -this->get_direction());
    // if(aux1-EPS > t_min && aux1 < t_max && aux1 < t){
    if (this->get_has_base() && comparator::g(aux1, t_min) && comparator::l(aux1, t_max) && comparator::l(aux1, t))
        t = aux1, n = -this->get_direction();
    return {t, n};
}

vp cone::normal_with_shell(vp &O, vp &D, double &t)
{
    vp P = O + D * t;
    vp w = (this->get_center() + (this->get_direction() * this->get_heigth())) - P;
    vp n_barra = w % this->get_direction();
    return ((n_barra % w) / ~(n_barra % w));
}

// transformations
void cone::transform()
{
    this->center = (this->transformations * matrix::vp_to_matrix(this->center)).matrix_to_vp();
    this->top = (this->transformations * matrix::vp_to_matrix(this->top)).matrix_to_vp();
    direction = (top - center) / ~(top - center);
    transformations = matrix::identity(4);
}

void cone::to_camera(matrix M)
{
    this->center = (M * matrix::vp_to_matrix(this->center)).matrix_to_vp();
    this->top = (M * matrix::vp_to_matrix(this->top)).matrix_to_vp();
    this->direction = (M * matrix::vp_to_matrix(this->direction, 0)).matrix_to_vp();
    this->direction = this->direction / ~this->direction;
}

void cone::scaling(vp S)
{
    this->radio = S.get_x();
    this->heigth = S.get_y();
    this->top = this->center + this->direction * this->heigth;
}

// Getters and Setters
vp cone::get_center() { return this->center; }
void cone::set_center(vp center) { this->center = center; }
vp cone::get_direction() { return this->direction; }
void cone::set_direction(vp direction) { this->direction = direction; }
double cone::get_radio() { return this->radio; }
void cone::set_radio(double radio) { this->radio = radio; }
double cone::get_heigth() { return this->heigth; }
void cone::set_heigth(double heigth) { this->heigth = heigth; }
bool cone::get_has_base() { return this->has_base; }
void cone::set_has_base(bool has_base) { this->has_base = has_base; }
