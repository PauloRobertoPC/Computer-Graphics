#ifndef CUBE_HPP
#define CUBE_HPP

#include "mesh.hpp"

class cube : public mesh {
    private:
        double width, heigth, length;
    
    public:
        cube();
        cube(px k_a, px k_d, px k_s, double s);
    
};

#endif
