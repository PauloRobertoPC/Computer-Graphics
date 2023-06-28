#ifndef SCENE_HPP
#define SCENE_HPP

#include "../objects/object.hpp"
#include "../utils/vp.hpp"
#include "../utils/px.hpp"
#include "../utils/ray.hpp"
#include "../utils/hit_info.hpp"
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

class tracer;

class scene
{
public:
    camera O;                    // camera
    viewport vw;                 // viewport
    canvas c;                    // canvas
    tracer *tr;                  // tracer
    PROJECTION p;                // projection used
    std::set<object *> objects;  // objects who are in the scene
    std::vector<light *> lights; // lights who are in the scene

    px compute_lighting(vp P, vp N, vp V, object *obj); // calculate all the light in an specific point


    bool without_shade(vp P, light *l);

    vp xy(int i, int j); // direction of the ray from the observer to the real world passing through the pixel i,j of the canvas

    ray ray_equation(int i, int j);
    vp refractRay(vp D, vp P, vp n, object *obj);

public:
    scene(camera O, viewport vw, canvas c, PROJECTION p, tracer* t);

    void add_object(object *o);
    void add_light(light *l);

    hit_info hit_objects(ray r, double t_min, int recursion_depth);

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
