#ifndef CUBE_HPP
#define CUBE_HPP

#include "mesh.hpp"

class cube : public mesh {
    private:
        double a;
    
    public:
        cube();
        cube(vp center, double a, px k_a, px k_d, px k_s, double s);

        //getters and setters
        double get_a();
        void set_a(double a);
    
};

#endif
