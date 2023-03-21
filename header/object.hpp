#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <tuple>
#include "vp.hpp"
#include "px.hpp"
#include "matrix.hpp"

class object
{
private:
    px k_a, k_d, k_s; // intensity of ambient, difuse ans specular light_reflection
    double specular;  // object's shineness
    double reflective;

    void rotation_auxiliar(matrix M);

protected:
    int width, height;
    bool has_image;
    px current_pixel_image;
    std::vector<std::vector<px>> image;
    matrix transformations;

public:
    object();
    object(px k_a, px k_d, px k_s, double specular, double reflective);
    object(const char *, double specular, double reflective);

    virtual vp get_def_point() = 0;

    // return scalar 't' and normal with the point of intersection with the object
    virtual std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max) = 0;

    // transformations
    virtual void to_camera(matrix M) = 0;
    virtual void transform() = 0;
    virtual void translation(vp P, bool point = true);
    virtual void rotation_x(double angle);
    virtual void rotation_y(double angle);
    virtual void rotation_z(double angle);
    virtual void rotate_arbitrary(vp o, vp direction, double angle);
    virtual void scaling(vp S) = 0;
    virtual void shear_xy(double angle);
    virtual void shear_yx(double angle);
    virtual void shear_xz(double angle);
    virtual void shear_zx(double angle);
    virtual void shear_yz(double angle);
    virtual void shear_zy(double angle);
    virtual void mirror_xy();
    virtual void mirror_xz();
    virtual void mirror_yz();
    virtual void mirror_arbitrary(vp n, vp p);

    // Getters and Setters
    virtual void set_pixel_image(int i, int j);
    bool get_has_image();
    px get_k_a();
    void set_k_a(px k_a);
    px get_k_d();
    void set_k_d(px k_d);
    px get_k_s();
    void set_k_s(px k_s);
    double get_specular();
    void set_specular(double specular);
    double get_reflective();
    void set_reflective(double reflective);
};

#endif
