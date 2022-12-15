#include <cmath>
#include "../header/light.hpp"

light::light(px intensity, char type_l) : intensity(intensity), save_intensity(intensity), type_l(type_l) {}

// Getters and Setters
px light::get_intensity() { return intensity; }
void light::set_intensity(px intensity) { this->intensity = intensity; }

void light::turn_off() { this->set_intensity(px(0, 0, 0)); }
void light::turn_on(px intensity)
{
    this->set_intensity(intensity);
    this->save_intensity = intensity;
}
void light::turn_on() { this->set_intensity(this->save_intensity); }
