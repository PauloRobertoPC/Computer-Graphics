#ifndef COMPLEX_OBJECT_HPP
#define COMPLEX_OBJECT_HPP

#include "mesh.hpp"

class complex_object : public mesh {
    private:
        double width, height, length;
    
        vp get_def_point();
    
    public:
        complex_object();
        complex_object(std::string name, px k_a, px k_d, px k_s, double s);

        // transformations 
        void scaling(vp S); //length, height, width
};

#endif
