#ifndef COMPLEX_OBJECT_HPP
#define COMPLEX_OBJECT_HPP

#include "mesh.hpp"
#include "cube.hpp"

class complex_object : public mesh
{
private:
    double width, height, length;
    cube *cluster;

    vp get_def_point();

public:
    complex_object();
    complex_object(std::string name, px k_a, px k_d, px k_s, double s, double reflective);

    std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);

    // transformations
    void to_camera(matrix M);
    void scaling(vp S);
    void translation(vp P, bool point = true);
    void rotation_x(double angle);
    void rotation_y(double angle);
    void rotation_z(double angle);
    void rotate_arbitrary(vp o, vp direction, double angle);
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
};

#endif
