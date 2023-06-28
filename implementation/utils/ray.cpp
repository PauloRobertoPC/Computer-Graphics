#include "../../header/utils/ray.hpp"

ray::ray(){
    O = D = vp(0, 0, 0);
}

ray::ray(vp O, vp D) : O(O), D(D){}
