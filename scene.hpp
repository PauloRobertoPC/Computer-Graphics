#ifndef SCENE_HPP
#define SCENE_HPP

#include <bits/stdc++.h>
#include "util.hpp"
#include "viewport.hpp"
#include "canvas.hpp"
#include "sphere.hpp"
#include "light.hpp"

using namespace std;

struct scene{
    vp O;                       //posição da câmera/obeservador
    viewport vw;                //viewport
    canvas c;                   //canvas
    vector<sphere> spheres;     //esferas que estão no cenário
    vector<light> lights;       //luzes que estão no cenário
    double dx, dy;              //lagura e altura de cada pixel/posição do canvas

    scene(vp O, viewport vw, canvas c) : O(O), vw(vw), c(c) {
        this->dx = 1.0*vw.w/c.m;
        this->dy = 1.0*vw.h/c.n; 
    }
    
    void add_sphere(sphere s){ spheres.push_back(s); }
    void add_light(light l){ lights.push_back(l); }
    
    
    double compute_lighting(vp P, vp N, vp V, int s){
        double i = 0.0;
        for(light l:lights){
            if(l.type == ambient){
                i += l.intensity;
            }else{
                vp L = (l.type == point ? l.position - P : l.direction);
                double ndl = N*L;
                //Difuse
                if(ndl > 0) i += l.intensity* ndl/((~N)*(~L));
                //Specular
                if(s != -1){
                    vp R = (N*(N*L))*2 - L;
                    double rdv = R*V;
                    if(rdv > 0) i += l.intensity * pow((rdv/((~R)*(~V))), s);
                }
            }
        }
        return i;
    }

    px trace_ray_spheres(vp O, vp D, double t_min, double t_max){
        sphere closest_sphere; px color = c.background_color; bool nulo = true;
        double t1, t2, closest = INF;
        for(sphere s:spheres){
            tie(t1, t2) = s.intersection_with_ray(O, D); 
            if(t1 >= t_min && t1 <= t_max && t1 < closest){
                closest = t1;
                closest_sphere = s;
                nulo = false;
            }
            if(t2 >= t_min && t2 <= t_max && t2 < closest){
                closest = t2;
                closest_sphere = s;
                nulo = false;
            }
        }
        if(nulo) return c.background_color;
        vp P = O + D*closest;
        vp N = (P-closest_sphere.center)/closest_sphere.radio;
        return closest_sphere.color * compute_lighting(P, N, -D, closest_sphere.specular);
    }
    
    vp xy(int i, int j){ //Canvas to Viewport
        return vp(-vw.w/2.0 + dx/2.0 + j*dx, vw.h/2.0 - dy/2.0 - i*dy, vw.d);
    }
    
    void draw_scenario(){
        for(int i = 0; i < c.n; i++){
            for(int j = 0; j < c.m; j++){
                vp D = xy(i, j); //Direção do raio do observador para o mundo real que passa pelo pixel i, j do canvas
                px color = trace_ray_spheres(this->O, D, 1.0, INF);
                c.to_color(i, j, color);
            }
        }
    }

    void save_scenario(const char* image_name){
        c.write_image(image_name);
    }
};

#endif
