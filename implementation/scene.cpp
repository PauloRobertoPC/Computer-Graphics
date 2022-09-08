#include <cmath>
#include "../header/scene.hpp"

scene::scene(vp O, viewport vw, canvas c) : O(O), vw(vw), c(c) {
    this->dx = 1.0*vw.get_w()/c.get_m();
    this->dy = 1.0*vw.get_h()/c.get_n(); 
}

double scene::compute_lighting(vp P, vp N, vp V, int s){
    double i = 0.0;
    for(light* l:lights)
        i += l->calculate_intensity(P, N, V, s);
    return i;
}

px scene::trace_ray_spheres(vp O, vp D, double t_min, double t_max){
    object* closest_object; px color = c.get_background_color(); bool nulo = true;
    double t1, t2, closest = INF;
    for(object* o:objects){
        std::tie(t1, t2) = o->intersection_with_ray(O, D); 
        if(t1 >= t_min && t1 <= t_max && t1 < closest){
            closest = t1;
            closest_object = o;
            nulo = false;
        }
        if(t2 >= t_min && t2 <= t_max && t2 < closest){
            closest = t2;
            closest_object = o;
            nulo = false;
        }
    }
    if(nulo) return c.get_background_color();
    vp P = O + D*closest;
    vp N = closest_object->normal(P);
    return closest_object->get_color() * compute_lighting(P, N, -D, closest_object->get_specular());
}

vp scene::xy(int i, int j){ 
    return vp(-vw.get_w()/2.0 + dx/2.0 + j*dx, vw.get_h()/2.0 - dy/2.0 - i*dy, vw.get_d());
}

void scene::add_object(object *o){ objects.push_back(o); }
void scene::add_light(light *l){ lights.push_back(l); }

void scene::draw_scenario(){
    for(int i = 0; i < c.get_n(); i++){
        for(int j = 0; j < c.get_m(); j++){
            vp D = xy(i, j); 
            px color = trace_ray_spheres(this->O, D, 1.0, INF);
            c.to_color(i, j, color);
        }
    }
}

void scene::save_scenario(const char* image_name){
    c.write_image(image_name);
}
