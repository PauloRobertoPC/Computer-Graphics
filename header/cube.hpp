#ifndef CUBE_HPP
#define CUBE_HPP

#include "mesh.hpp"

class cube : public mesh {
    private:
        double width, heigth, length;
    
    public:
        cube();
        cube(px k_a, px k_d, px k_s, double s);

        //transformations
        void transform();
        void translation(vp P);
        void rotation_x(double angle);
        void rotation_y(double angle);
        void rotation_z(double angle);
        void scaling(vp S);
        void shear_xy(double angle);
        void shear_yx(double angle);
        void shear_xz(double angle);
        void shear_zx(double angle);
        void shear_yz(double angle);
        void shear_zy(double angle);
        void mirror_xy();
        void mirror_xz();
        void mirror_yz();
        void mirror_arbitrary(vp n, vp p);
        void rotate_arbitrary(vp o, vp direction, double angle);
};

#endif
