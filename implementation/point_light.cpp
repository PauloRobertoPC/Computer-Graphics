#include <bits/stdc++.h>
#include "../header/point_light.hpp"
#include "../header/comparator.hpp"

point_light::point_light(px intensity, vp position) : specular_light(intensity), position(position) {}

px point_light::calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate)
{
    px i(0, 0, 0);
    if (!calculate)
        return i;
    vp L = this->get_position() - P;
    L = L / (~L);
    double ndl = N * L;
    if (ndl > 0.0)
        i = i + (obj->get_k_d() * (this->get_intensity() * ndl));
    i = i + specular(N, L, V, obj);
    return i;
}

vp point_light::get_l(vp P)
{
    return this->get_position() - P;
}

void point_light::to_camera(matrix M)
{
    this->position = (M * matrix::vp_to_matrix(this->position)).matrix_to_vp();
}

void point_light::translation(vp v)
{
    matrix M = matrix::translation_matrix(v);
    this->position = (M * matrix::vp_to_matrix(this->position)).matrix_to_vp();
}

void point_light::print_light()
{
    std::cout << "LUZ PONTUAL - (" << this->position.get_x() << ", " << this->position.get_y() << ", " << this->position.get_z() << ")";
}

void point_light::change_angle(double a)
{
}
void point_light::change_direction(vp d)
{
}

// Getters and Setters
vp point_light::get_position() { return this->position; }
void point_light::set_position(vp position) { this->position = position; }
