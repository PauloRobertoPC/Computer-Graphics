#ifndef CILINDER_HPP
#define CILINDER_HPP

#include "object.hpp"
#include "vp.hpp"
#include <tuple>

class cilinder : public object
{
private:
    vp center, direction, top;
    double radio, heigth;
    bool has_base, has_top;

    bool in_shell(vp P);
    bool in_base(vp P, vp p_pi, vp n);
    std::tuple<double, double> ray_intersect_cylinder_shell_vector(vp O, vp D);
    double ray_intersect_base(vp O, vp D, vp p_pi, vp n);
    vp normal_with_shell(vp &O, vp &D, double &t);

public:
    cilinder();
    cilinder(vp center, vp direction, double r, double heigth, px k_a, px k_d, px k_s, double s, double reflective, bool has_base, bool has_top);
    cilinder(vp center, vp top, double r, px k_a, px k_d, px k_s, double s, double reflective, bool has_base, bool has_top);

    vp get_def_point();

    std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);

    // transformations
    void to_camera(matrix M);
    void transform();
    void scaling(vp S);

    // Getters and Setters
    vp get_center();
    void set_center(vp center);
    vp get_direction();
    void set_direction(vp direction);
    double get_radio();
    void set_radio(double radio);
    double get_heigth();
    void set_heigth(double radio);
    bool get_has_base();
    void set_has_base(bool has_base);
    bool get_has_top();
    void set_has_top(bool has_top);
};

#endif
