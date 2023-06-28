#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../utils/px.hpp"
#include "../utils/hit_info.hpp"
#include "../world/scene.hpp"  // required for the shade function in all derived classes

class material {
public:

    material() = default;

    virtual ~material();

    material(const material& material);

    material(material&& material) noexcept;

    material& operator=(const material& material);

    material& operator=(material&& material) noexcept;

    virtual material* clone() const = 0;

    virtual px shade(hit_info& sr);

    virtual px path_shade(hit_info& sr);

    virtual px global_shade(hit_info& sr);

    // 18.6 Other materials
    // It has to be defined for every material tha we want to render with area-light shading
    virtual px area_light_shade(hit_info& sr);

    virtual px get_Le(hit_info& sr) const;

protected:

    // From the book, chapter 16.7 Shadowing Options
    // Allows us to specify whether a material has shadows cast on it or not.
    // This is sometimes necessary for shading objects inside transparent objects
    // without having to render caustics (see Sections 28.7 and 28.8)
    bool shadows = true;
};

#endif
