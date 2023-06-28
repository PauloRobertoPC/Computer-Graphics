#ifndef RAY_HPP
#define RAY_HPP

#include "vp.hpp"
#include <math.h>

class ray
{
public:
    vp O; // origin point
    vp D; // direction

    ray();
    ray(vp O, vp D);

    static vp reflection_ray(vp R, vp N)
    {
        vp RR = N * 2.0 * (N * R) - R;
        return (RR/(~RR));
    }

    static vp refracted_ray(vp I, vp N, double ni, double nt){
        double nr = ni/nt; 
        double dentro_raiz = 1-nr*nr*(1-(N*I)*(N*I)); 
        if(dentro_raiz < 0) return vp(0, 0, 0);
        vp T = N*(nr*(N*I) - sqrt(dentro_raiz)) - I*nr;
        return (T/(~T));
    }
};

#endif
