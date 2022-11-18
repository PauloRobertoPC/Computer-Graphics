#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "px.hpp"
#include "matrix.hpp"

class camera{
    private:
        vp i, j, k;
        matrix w2c, c2w;
    
    public:
        camera(vp E, vp look_at, vp up);
        vp world_to_camera(vp p); 
        vp camera_to_world(vp p);

        matrix get_w2c();
        matrix get_c2w();
        vp get_i();
        vp get_j();
        vp get_k();

        void change_view(vp E, vp look_at, vp up);
};

#endif
