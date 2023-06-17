#include "../../header/lights/ambient_light.hpp"

ambient_light::ambient_light(px intensity, char type_l) : light(intensity, type_l) {}

px ambient_light::calculate_intensity(vp P, vp N, vp V, object *obj, bool calculate)
{
    return obj->get_k_a() * this->get_intensity();
}

void ambient_light::to_camera(matrix M) {}

vp ambient_light::get_l(vp P) { return vp(0, 0, 0); }

void ambient_light::translation(vp v) {}
void ambient_light::print_light()
{
    std::cout << "LUZ AMBIENTE";
}

void ambient_light::change_angle(double a)
{
}
void ambient_light::change_direction(vp d)
{
}
