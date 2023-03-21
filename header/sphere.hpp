#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "px.hpp"
#include "vp.hpp"
#include <tuple>

class sphere : public object
{
private:
    vp center;
    double radio;

public:
    sphere();
    sphere(vp center, double r, px k_a, px k_d, px k_s, double s, double reflective);

    vp get_def_point();

    // calculate the intersections between the sphere and the ray
    std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);
    vp normal_with_shell(vp &O, vp &D, double &t);
    vp normal(vp P);

    // transformations
    void to_camera(matrix M);
    void transform();
    void scaling(vp S);

    // Getters and Setters
    vp get_center();
    void set_center(vp center);
    double get_radio();
    void set_radio(double radio);
};

#endif
