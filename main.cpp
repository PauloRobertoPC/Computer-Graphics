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

using namespace std;

int main(){
    double d = 30;
    vp O(0, 0, 0);
    viewport vw(60, 60, -d);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));

    scene cena(O, vw, c);

    double R = 40;
    cena.add_object(new sphere(vp(0, 0, -100), R, px(0.7, 0.2, 0.2), px(0.7, 0.2, 0.2), px(0.7, 0.2, 0.2), 10)); 
    cena.add_object(new plan(vp(0, -R, 0), vp(0, 1, 0), px(0.2, 0.7, 0.2), px(0.2, 0.7, 0.2), px(0.0, 0.0, 0.0), 1)); 
    cena.add_object(new plan(vp(0, 0, -200), vp(0, 0, 1), px(0.3, 0.3, 0.7), px(0.3, 0.3, 0.7), px(0.0, 0.0, 0.0), 1)); 
    
    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    cena.add_light(new point_light(px(0.7, 0.7, 0.7), vp(0, 60, -30)));
     
    cena.draw_scenario(); //Execute the ray tracing

    cena.save_scenario("sphere.png"); //Save image in "sphere.png"

    return 0;
}
