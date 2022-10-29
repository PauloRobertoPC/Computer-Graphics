#ifndef CUBE_HPP
#define CUBE_HPP

#include "mesh.hpp"

class cube : public mesh {
    private:
        double width, height, length;
    
        vp get_def_point();
    
    public:
        cube();
        cube(px k_a, px k_d, px k_s, double s);

        // transformations 
        void scaling(vp S); //length, height, width
};

#endif
