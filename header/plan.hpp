#ifndef PLAN_HPP
#define PLAN_HPP

#include "object.hpp"
#include "px.hpp"
#include "vp.hpp"
#include <tuple>

class plan : public object
{
private:
    vp p_pi, n; // p_pi = Point in Plan, n = vector normal with the plan

public:
    plan();
    plan(vp p_pi, vp n);
    plan(vp p_pi, vp n, px k_a, px k_d, px k_s, double s, double reflective);
    plan(vp p_pi, vp n, const char *name, double s, double reflective);

    vp get_def_point();

    std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);

    // transformations
    void to_camera(matrix M);
    void translation(vp P, bool point = true);
    void rotation_x(double angle);
    void rotation_y(double angle);
    void rotation_z(double angle);
    void rotate_arbitrary(vp o, vp direction, double angle);
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
    void transform();

    // Getters and Setters
    vp get_p_pi();
    void set_p_pi(vp p_pi);
    vp get_n();
    void set_n(vp n);
};

#endif
