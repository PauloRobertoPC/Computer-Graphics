#include "header/vp.hpp"
#include "header/px.hpp"
#include "header/viewport.hpp"
#include "header/canvas.hpp"
#include "header/sphere.hpp"
#include "header/scene.hpp"
#include "header/ambient_light.hpp"
#include "header/point_light.hpp"
#include "header/direction_light.hpp"
#include "header/plan.hpp"
#include "header/matrix.hpp"
#include "header/cilinder.hpp"
#include "header/cone.hpp"
#include "header/mesh.hpp"
#include "header/cube.hpp"
#include "header/camera.hpp"
#include <cmath>
#include <iostream>

using namespace std;

int main(){
    camera O(vp(0, 0, 0), vp(0, 0, -1), vp(1, 1, -1));
    viewport vw(60, 60, -20);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));

    scene cena(O, vw, c);

    cube* cuboa = new cube(px(1., 0.078, 0.576), px(1., 0.078, 0.576), px(1., 0.078, 0.576), 10);
    cuboa->mirror_xy();
    cuboa->scaling(vp(100, 50, 50));
    cuboa->transform();
    cuboa->translation(vp(0, 100, -165));
    cuboa->transform();
    cena.add_object(cuboa);
    
    cube* cubob = new cube(px(1., 0.078, 0.576), px(1., 0.078, 0.576), px(1., 0.078, 0.576), 10);
    cubob->scaling(vp(100, 50, 50));
    cubob->transform();
    cubob->mirror_xy(); 
    cubob->translation(vp(0, -100, -165));
    cubob->transform();
    cena.add_object(cubob);
    
    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    cena.add_light(new point_light(px(0.7, 0.7, 0.7), vp(-100, 140, -20)));
     
    cena.draw_scenario(); //Execute the ray tracing

    cena.save_scenario("image.png"); //Save image in "image.png"

    return 0;
}
