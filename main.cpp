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
#include <cmath>

using namespace std;

int main(){
    vp O(0, 0, 0);
    viewport vw(60, 60, -25);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));

    scene cena(O, vw, c);

    cube* cuboa = new cube(px(1., 0.078, 0.576), px(1., 0.078, 0.576), px(1., 0.078, 0.576), 10);
    // cuboa->rotation_x(0.785398);
    // cuboa->rotation_y(0.785398);
    // cuboa->rotation_z(0.785398);
    // cuboa->transform();
    cuboa->scaling(vp(50, 50, 50));
    cuboa->transform();
    // cuboa->shear_xy(0.785398);
    cuboa->shear_yx(0.785398);
    // cuboa->shear_xz(0.785398);
    // cuboa->shear_zx(0.785398);
    // cuboa->shear_yz(0.785398);
    // cuboa->shear_zy(0.785398);
    cuboa->transform();
    cuboa->translation(vp(0, 100, -165));
    cuboa->transform();
    
    cube* cubob = new cube(px(1., 0.078, 0.576), px(1., 0.078, 0.576), px(1., 0.078, 0.576), 10);
    cubob->scaling(vp(50, 50, 50));
    cubob->transform();
    cubob->shear_yx(0.785398);
    cubob->transform();
    cubob->mirror_yz();
    cubob->transform();
    cubob->translation(vp(50, 100, -165));
    cubob->transform();
    
    cena.add_object(cuboa);
    cena.add_object(cubob);

    // cena.add_object(new cilinder(vp(0, -150, -200), vp(0, 1, 0), 5, 90, px(0.824, 0.706, 0.549), px(0.824, 0.706, 0.549), px(0.824, 0.706, 0.549), 10, true, true)); 
    // cena.add_object(new cone(vp(0, -60, -200), vp(0, 1, 0), 90, 150, px(0, 1, 0.498), px(0, 1, 0.498), px(0, 1, 0.498),  10, true)); 
    // cena.add_object(new cube(vp(0, -150, -165), 40, px(1., 0.078, 0.576), px(1., 0.078, 0.576), px(1., 0.078, 0.576), 10));
    // cena.add_object(new sphere(vp(0, 95, -200), 5, px(0.854, 0.647, 0.125), px(0.854, 0.647, 0.125), px(0.854, 0.647, 0.125), 10)); 
    // 
    // cena.add_object(new plan(vp(0, -150, 0), vp(0, 1, 0), px(0.2, 0.7, 0.2), px(0.2, 0.7, 0.2), px(0.0, 0.0, 0.0), 1)); 
    // cena.add_object(new plan(vp(200, -150, 0), vp(-1, 0, 0), px(0.686, 0.933, 0.933),px(0.686, 0.933, 0.933),px(0.686, 0.933, 0.933), 1)); 
    // cena.add_object(new plan(vp(200, -150, -400), vp(0, 0, 1), px(0.686, 0.933, 0.933),px(0.686, 0.933, 0.933),px(0.686, 0.933, 0.933), 1)); 
    // cena.add_object(new plan(vp(-200, -150, 0), vp(1, 0, 0), px(0.686, 0.933, 0.933),px(0.686, 0.933, 0.933),px(0.686, 0.933, 0.933), 1)); 
    // cena.add_object(new plan(vp(0, 150, 0), vp(0, -1, 0), px(0.933, 0.933, 0.933),px(0.933, 0.933, 0.933),px(0.933, 0.933, 0.933), 1)); 
    //
    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    cena.add_light(new point_light(px(0.7, 0.7, 0.7), vp(-100, 140, -20)));
     
    cena.draw_scenario(); //Execute the ray tracing

    cena.save_scenario("image.png"); //Save image in "image.png"

    return 0;
}
