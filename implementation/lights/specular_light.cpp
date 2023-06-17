#include <cmath>
#include "../../header/lights/specular_light.hpp"

specular_light::specular_light(px intensity, char type_l) : light(intensity, type_l) {}

px specular_light::specular(vp N, vp L, vp V, object *obj)
{
    if (obj->get_specular() != -1)
    {
        vp R = (N * (N * L)) * 2 - L;
        double rdv = R * V;
        if (rdv > 0.0)
            return (obj->get_k_s() * (this->get_intensity() * pow(rdv, obj->get_specular())));
    }
    return px(0, 0, 0);
}

void specular_light::change_angle(double a)
{
}
void specular_light::change_direction(vp d)
{
}
