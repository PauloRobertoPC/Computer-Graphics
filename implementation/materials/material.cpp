#include "../../header/materials/material.hpp"

#include <utility>

material::material(const material& material) : shadows(material.shadows) {}

material::material(material&& material) noexcept : shadows(std::exchange(material.shadows, true)) {}

material& material::operator=(const material& material) {
    shadows = material.shadows;
    return *this;
}

material& material::operator=(material&& material) noexcept {
    shadows = std::exchange(material.shadows, true);
    return *this;
}

material::~material() {}

px material::shade([[maybe_unused]] hit_info& sr) { return px(0, 0, 0); }

px material::path_shade(hit_info& sr) { return shade(sr); }

px material::global_shade(hit_info& sr) { return shade(sr); }

px material::area_light_shade(hit_info& sr) { return shade(sr); }

px material::get_Le(hit_info& sr) const { return px(0, 0, 0); }
