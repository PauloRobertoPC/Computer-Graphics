#include <bits/stdc++.h>
#include <cmath>
#include "../header/scene.hpp"
#include "../header/comparator.hpp"
#include "../header/camera.hpp"
#include "../header/plan.hpp"

scene::scene(camera O, viewport vw, canvas c, PROJECTION p) : O(O), vw(vw), c(c), p(p)
{
    this->dx = 1.0 * vw.get_w() / c.get_m();
    this->dy = 1.0 * vw.get_h() / c.get_n();
}

void scene::change_dx_dy()
{
    this->dx = 1.0 * vw.get_w() / c.get_m();
    this->dy = 1.0 * vw.get_h() / c.get_n();
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

vp scene::reflection_ray(vp R, vp N)
{
    return N * 2.0 * (N * R) - R;
}

px scene::compute_lighting(vp P, vp N, vp V, object *obj)
{
    px i(0, 0, 0);
    for (light *l : lights)
        i = i + l->calculate_intensity(P, N, V, obj, without_shade(P, l));
    return i;
}

std::tuple<px, object *> scene::trace_ray(vp O, vp D, double t_min, double t_max, int i, int j, int recursion_depth)
{
    object *closest_object = nullptr;
    bool nulo = true;
    double t, closest = INF;
    vp aux, n;
    for (object *o : objects)
    {
        std::tie(t, aux) = o->intersection_with_ray(O, D, t_min, t_max);
        // if(t-EPS > t_min && t < t_max && t < closest){
        if (comparator::g(t, t_min) && comparator::l(t, t_max) && comparator::l(t, closest))
        {
            closest = t;
            n = aux;
            closest_object = o;
            nulo = false;
        }
    }
    if (nulo)
        return {c.get_background_color(), closest_object};
    if (closest_object->get_has_image())
        closest_object->set_pixel_image(i, j);
    vp P = O + D * closest;
    if (comparator::g(D * n, 0))
        n = -n;

    px local_color = compute_lighting(P, n, -D, closest_object);

    // reflective
    double reflex = closest_object->get_reflective();
    if (recursion_depth <= 0 || reflex <= 0)
        return {local_color, closest_object};

    px reflected_color;
    object *reflected_obj;
    vp R = reflection_ray(-D, n);
    std::tie(reflected_color, reflected_obj) = this->trace_ray(P, R, 0.001, INF, i, j, recursion_depth - 1);
    return {local_color * (1 - reflex) + reflected_color * reflex, closest_object};
}

vp scene::xy(int i, int j)
{
    return vp(-vw.get_w() / 2.0 + dx / 2.0 + j * dx, vw.get_h() / 2.0 - dy / 2.0 - i * dy, vw.get_d());
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

std::tuple<vp, vp> scene::ray_equation(int i, int j)
{
    vp D = xy(i, j);
    switch (this->p)
    {
    case PERSPECITVE:
        return {vp(0, 0, 0), (D / (~D))};
        break;
    case PARALELL:
        return {D, vp(0, 0, -1)};
        break;
    }
    return {vp(0, 0, 0), vp(0, 0, 0)};
}

void scene::change_projection(PROJECTION p)
{
    this->p = p;
}

void scene::draw_scenario(bool change_coordinates)
{
    if (change_coordinates)
        transform_scenario_to_camera();
    px color;
    object *choosen_object;
    vp O, D;
    for (int i = 0; i < c.get_n(); i++)
    {
        for (int j = 0; j < c.get_m(); j++)
        {
            std::tie(O, D) = ray_equation(i, j);
            std::tie(color, choosen_object) = trace_ray(O, D, 1.0, INF, i, j);
            c.to_color(i, j, color, choosen_object);
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
    vw.set_w(w);
    vw.set_h(h);
    change_dx_dy();
}

void scene::change_d(double d)
{
    vw.set_d(d);
}

void scene::translation(object *choosen_object, int i, int j)
{
    plan p(choosen_object->get_def_point(), vp(0, 0, 1));
    vp n, O, D;
    std::tie(O, D) = ray_equation(i, j);
    double t;
    std::tie(t, n) = p.intersection_with_ray(O, D, 1, INF);
    vp P = D * t;
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
