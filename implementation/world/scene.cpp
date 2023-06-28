#include <bits/stdc++.h>
#include <cmath>
#include "../../header/world/scene.hpp"
#include "../../header/objects/plan.hpp"
#include "../../header/utils/comparator.hpp"
#include "../../header/cameras/camera.hpp"
#include "../../header/objects/plan.hpp"
#include "../../header/tracers/tracer.hpp"

scene::scene(camera O, viewport vw, canvas c, PROJECTION p, tracer* t) : O(O), vw(vw), c(c), p(p), tr(t){
    tr->set_scene(this);
}

bool scene::without_shade(vp P, light *l)
{
    double t, t_min = 1, t_max = INF, closest = INF;
    vp n;
    vp L = l->get_l(P);
    if ((~L) == 0.0)
        return true;
    vp NL = L / (~L);
    for (object *o : objects)
    {
        std::tie(t, n) = o->intersection_with_ray(P, NL, t_min, t_max);
        // if(t-EPS > t_min && t < t_max && t < closest) closest = t;
        if (comparator::g(t, t_min) && comparator::l(t, closest))
            closest = t;
    }

    if (l->type_l == 'd')
        return closest == INF;

    return (closest >= (~L));
}

px scene::compute_lighting(vp P, vp N, vp V, object *obj)
{
    px i(0, 0, 0);
    for (light *l : lights)
        i = i + l->calculate_intensity(P, N, V, obj, without_shade(P, l));
    return i;
}

hit_info scene::hit_objects(ray r, double t_min, int recursion_depth)
{
    hit_info hi; hi.r = r; hi.depth = recursion_depth;
    double t_max = INF;

    double t = INF;
    vp normal;
    for (object *o : objects)
    {
        std::tie(t, normal) = o->intersection_with_ray(r.O, r.D, t_min, t_max);
        if (comparator::g(t, t_min) && comparator::l(t, t_max) && comparator::l(t, hi.t))
        {
            hi.t = t;
            hi.normal = normal;
            hi.closest_object = o;
            hi.hit_an_object = true;
        }
    }

    if (!hi.hit_an_object)
        return hi;

    hi.hit_point = r.O + r.D * hi.t;
    if (comparator::g(r.D * hi.normal, 0))
        hi.normal = -hi.normal;

    return hi;
}

vp scene::xy(int i, int j)
{
    return vp(-vw.get_w() / 2.0 + vw.get_dx() / 2.0 + j * vw.get_dx(), vw.get_h() / 2.0 - vw.get_dy() / 2.0 - i * vw.get_dy(), vw.get_d());
}

void scene::add_object(object *o) { objects.insert(o); }
void scene::add_light(light *l) { lights.push_back(l); }

void scene::transform_scenario_to_camera()
{
    for (object *o : objects)
        o->to_camera(O.get_w2c());
    for (light *l : lights)
        l->to_camera(O.get_w2c());
}

void scene::transform_scenario_to_world()
{
    for (object *o : objects)
        o->to_camera(O.get_c2w());
    for (light *l : lights)
        l->to_camera(O.get_c2w());
}

ray scene::ray_equation(int i, int j)
{
    vp D = xy(i, j);

    point_2D p2d = vw.sample_square();
    D.set_x(D.get_x()+p2d.x);
    D.set_y(D.get_y()+p2d.y);

    switch (this->p)
    {
    case PERSPECITVE:
        return ray(vp(0, 0, 0), (D / (~D)));
        break;
    case PARALELL:
        return ray(D, vp(0, 0, -1));
        break;
    }
    return ray(vp(0, 0, 0), vp(0, 0, 0));
}

void scene::change_projection(PROJECTION p)
{
    this->p = p;
}

void scene::draw_scenario(bool change_coordinates, int recursion_depth)
{
    if (change_coordinates)
        transform_scenario_to_camera();
    float tmin = 0.001;
    px color;
    object *choosen_object;
    ray d;
    for (int i = 0; i < c.get_n(); i++)
    {
        for (int j = 0; j < c.get_m(); j++)
        {
            px acm = px(0, 0, 0);
            color = px(0, 0, 0);
            for(int k = 0; k < vw.qnt_samples(); k++){
                d = ray_equation(i, j);
                std::tie(color, choosen_object) = tr->trace_ray(d, tmin, recursion_depth);
                acm = acm+color;
            }
            c.to_color(i, j, acm/vw.qnt_samples(), choosen_object);
        }
    }
    std::cout << "DESENHO CONCLUIDO\n";
}

object *scene::select_object(int i, int j) { return c.get_object(i, j); }
light *scene::select_light(int i)
{
    if (i > this->lights.size() && i < 1)
        return nullptr;
    return this->lights[i - 1];
}

void scene::print_lights()
{
    for (int i = 0; i < this->lights.size(); i++)
    {
        std::cout << '(' << i + 1 << ") - ";
        this->lights[i]->print_light();
        std::cout << std::endl;
    }
}

void scene::del_object(object *o)
{
    objects.erase(o);
}

void scene::change_view(vp E, vp look_at, vp up)
{
    this->transform_scenario_to_world();
    this->O.change_view(E, look_at, up);
    this->transform_scenario_to_camera();
}

void scene::change_vp(double w, double h)
{
    vw.set_wh(w, h);
}

void scene::change_d(double d)
{
    vw.set_d(d);
}

void scene::translation(object *choosen_object, int i, int j)
{
    plan p(choosen_object->get_def_point(), vp(0, 0, 1));
    vp n;
    ray d = ray_equation(i, j);
    double t;
    std::tie(t, n) = p.intersection_with_ray(d.O, d.D, 1, INF);
    vp P = d.D * t;
    P.print();
    choosen_object->translation(P);
}

px scene::get_pixel(int i, int j)
{
    return c.get_color(i, j);
}

void scene::save_scenario(const char *image_name)
{
    c.write_image(image_name);
}
