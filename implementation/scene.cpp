#include <bits/stdc++.h>
#include <cmath>
#include "../header/scene.hpp"
#include "../header/comparator.hpp"
#include "../header/camera.hpp"

scene::scene(camera O, viewport vw, canvas c) : O(O), vw(vw), c(c) {
    this->dx = 1.0*vw.get_w()/c.get_m();
    this->dy = 1.0*vw.get_h()/c.get_n(); 
}

bool scene::without_shade(vp P, light* l){
    double t, t_min = 1, t_max = INF, closest = INF; vp n;
    vp L = l->get_l(P); 
    if((~L) == 0.0) return true;
    vp NL = L/(~L);
    for(object* o:objects){
        std::tie(t, n) = o->intersection_with_ray(P, NL, t_min, t_max); 
        // if(t-EPS > t_min && t < t_max && t < closest) closest = t;
        if(comparator::g(t, t_min) && comparator::l(t, closest)) closest = t;
    }
    return (closest >= (~L));
}

px scene::compute_lighting(vp P, vp N, vp V, object* obj){
    px i(0, 0, 0);
    for(light* l:lights)
        i = i+l->calculate_intensity(P, N, V, obj, without_shade(P, l));
    return i;
}

px scene::trace_ray(vp O, vp D, double t_min, double t_max){
    object* closest_object; bool nulo = true;
    double t, closest = INF; vp aux, n;
    for(object* o:objects){
        std::tie(t, aux) = o->intersection_with_ray(O, D, t_min, t_max); 
        // if(t-EPS > t_min && t < t_max && t < closest){
        if(comparator::g(t, t_min) && comparator::l(t, t_max) && comparator::l(t, closest)){
            closest = t;
            n = aux;
            closest_object = o;
            nulo = false;
        }
    }
    if(nulo) return c.get_background_color();
    vp P = O + D*closest;
    if(comparator::g(D*n, 0)) n = -n;
    return compute_lighting(P, n, -D, closest_object);
}

vp scene::xy(int i, int j){ 
    return vp(-vw.get_w()/2.0 + dx/2.0 + j*dx, vw.get_h()/2.0 - dy/2.0 - i*dy, vw.get_d());
}

void scene::add_object(object *o){ objects.push_back(o); }
void scene::add_light(light *l){ lights.push_back(l); }

void scene::transform_scenario_to_camera(){
    for(object *o:objects) o->to_camera(O.get_w2c());
    for(light *l:lights) l->to_camera(O.get_w2c());
}

void scene::draw_scenario(){
    transform_scenario_to_camera();
    for(int i = 0; i < c.get_n(); i++){
        for(int j = 0; j < c.get_m(); j++){
            vp D = xy(i, j); D = D/(~D);
            px color = trace_ray(vp(0, 0, 0), D, 1.0, INF); //Perspectiva
            // px color = trace_ray(D, vp(0, 0, -1), 1.0, INF); //Paralela Ortogrâfica
            c.to_color(i, j, color);
        }
    }
}

px scene::get_pixel(int i, int j){
    return c.get_color(i, j);
}

void scene::save_scenario(const char* image_name){
    c.write_image(image_name);
}
