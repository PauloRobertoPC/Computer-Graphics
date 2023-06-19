#ifndef SCENE_HPP
#define SCENE_HPP

#include "../objects/object.hpp"
#include "../utils/vp.hpp"
#include "../utils/px.hpp"
#include "viewport.hpp"
#include "canvas.hpp"
#include "../objects/sphere.hpp"
#include "../lights/light.hpp"
#include "../cameras/camera.hpp"
#include <set>

enum PROJECTION
{
    PERSPECITVE,
    PARALELL
};

class scene
{
private:
    camera O;                    // camera
    viewport vw;                 // viewport
    canvas c;                    // canvas
    PROJECTION p;                // projection used
    std::set<object *> objects;  // objects who are in the scene
    std::vector<light *> lights; // lights whoa are in the scene

    px compute_lighting(vp P, vp N, vp V, object *obj); // calculate all the light in an specific point

    std::tuple<px, object *> trace_ray(vp O, vp D, double t_min, double t_max, int i, int j, int recursion_depth, double ni); // trace rays of from observer to direction D
    vp reflection_ray(vp r, vp n);
    vp refracted_ray(vp I, vp N, double ni, double nt);

    bool without_shade(vp P, light *l);

    vp xy(int i, int j); // direction of the ray from the observer to the real world passing through the pixel i,j of the canvas

    std::tuple<vp, vp> ray_equation(int i, int j);
    bool fresnel(vp D, vp n, object *obj, double & kr);
    vp refractRay(vp D, vp P, vp n, object *obj);

public:
    scene(camera O, viewport vw, canvas c, PROJECTION p);

    void add_object(object *o);
    void add_light(light *l);

    void draw_scenario(bool change_coordinates, int recursion_depth = 0);

    void save_scenario(const char *image_name);

    object *select_object(int i, int j);
    light *select_light(int i);

    void del_object(object *o);

    void translation(object *choosen_object, int i, int j);

    px get_pixel(int i, int j);

    void transform_scenario_to_camera();

    void transform_scenario_to_world();

    void print_lights();

    void change_projection(PROJECTION p);

    void change_view(vp E, vp look_at, vp up);

    void change_vp(double w, double h);
    void change_d(double d);
};

#endif
