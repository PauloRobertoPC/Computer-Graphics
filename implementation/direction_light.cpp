#include "../header/direction_light.hpp"

direction_light::direction_light(px intensity, vp direction) : specular_light(intensity), direction(direction) {}

px direction_light::calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate)
{
    px i(0, 0, 0);
    if (!calculate)
        return i;
    vp L = get_direction();
    double ndl = N * (L / ~L);
    if (ndl > 0.0)
        i = i + (obj->get_k_d() * (this->get_intensity() * ndl) / ((~N) * (~L)));
    i = i + specular(N, L, V, obj);
    return i;
}

vp direction_light::get_l(vp P) { return -get_direction(); }

void direction_light::to_camera(matrix M)
{
    this->direction = (M * matrix::vp_to_matrix(this->direction, 0)).matrix_to_vp();
    this->direction = this->direction / ~direction;
}

// Getters and Setters
vp direction_light::get_direction() { return this->direction; }
void direction_light::set_direction(vp direction) { this->direction = direction; }

void direction_light::translation(vp v)
{
    matrix M = matrix::translation_matrix(v);
    this->direction = (M * matrix::vp_to_matrix(this->direction, 0)).matrix_to_vp();
    this->direction = this->direction / ~direction;
}

void direction_light::print_light()
{
    std::cout << "LUZ DIRECIONAL - (" << this->direction.get_x() << ", " << this->direction.get_y() << ", " << this->direction.get_z() << ")";
}

void direction_light::change_angle(double a)
{
}
void direction_light::change_direction(vp d)
{
    this->direction = (d / ~d);
}