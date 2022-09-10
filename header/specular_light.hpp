#ifndef SPECULAR_LIGHT_HPP
#define SPECULAR_LIGHT_HPP

#include "vp.hpp"
#include "light.hpp"

class specular_light : public light{
    public:
        specular_light(px intensity);
    
        px specular(vp N, vp L, vp V, object* obj);
};

#endif
