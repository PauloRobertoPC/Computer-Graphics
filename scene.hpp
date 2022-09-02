#ifndef SCENE_HPP
#define SCENE_HPP

#include <bits/stdc++.h>
#include "util.hpp"
#include "viewport.hpp"
#include "canvas.hpp"
#include "sphere.hpp"

using namespace std;


struct scene{
    vp O;                       //posição da câmera/obeservador
    viewport vw;                //viewport
    canvas c;                   //canvas
    vector<sphere> spheres;     //esferas que estão no cenário
    

    scene(vp O, viewport vw, canvas c) : O(O), vw(vw), c(c) {}
    
    void add_sphere(sphere s){ spheres.push_back(s); }
    
    tuple <double, px> trace_ray_spheres(vp O, vp D, double t_min, double t_max){
        px background_color = c.background_color;
        double t1, t2, closest = INF;
        for(sphere s:spheres){
            tie(t1, t2) = s.intersection_with_ray(O, D); 
            if(t1 >= t_min && t1 <= t_max && t1 < closest){
                closest = t1;
                background_color = s.color;
            }
            if(t2 >= t_min && t2 <= t_max && t2 < closest){
                closest = t2;
                background_color = s.color;
            }
        }
        return {closest, background_color};
    }
    
    void draw_scenario(){
        for(int i = 0; i < c.n; i++){
            for(int j = 0; j < c.m; j++){
                double closest = INF; px color;
                vp D = c.xy(i, j); //Direção do raio para o mundo real que passa pelo pixel i, j do canvas
                tie(closest, color) = trace_ray_spheres(this->O, D, 1.0, INF);
                c.to_color(i, j, color);
            }
        }
    }

    void save_scenario(const char* image_name){
        c.write_image(image_name);
    }
};

#endif
