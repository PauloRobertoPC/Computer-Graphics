#include "header/vp.hpp"
#include "header/px.hpp"
#include "header/viewport.hpp"
#include "header/canvas.hpp"
#include "header/sphere.hpp"
#include "header/scene.hpp"
#include "header/ambient_light.hpp"
#include "header/point_light.hpp"
#include "header/direction_light.hpp"

using namespace std;

int main(){
    vp O(0, 0, 0); //Observer's point
    viewport vw(1, 1, 1); //Vh, Vw, point in z-axis
    canvas c(500, 500, px::convert_rgb(255, 255, 255)); //Ch, Cw, background_color

    scene cena(O, vw, c); //scene
    
    cena.add_object(new sphere(0, -1, 3, 1, 500, px::convert_rgb(255, 0, 0))); //sphere(x, y, z), radio, and sphere color
    cena.add_object(new sphere(2, 0, 4, 1, 500, px::convert_rgb(0, 0, 255))); //sphere(x, y, z), radio, and sphere color
    cena.add_object(new sphere(-2, 0, 4, 1, 10, px::convert_rgb(0, 255, 0))); //sphere(x, y, z), radio, and sphere color
    cena.add_object(new sphere(0, -5001, 0, 5000, 1000, px::convert_rgb(255, 255, 0))); //sphere(x, y, z), radio, and sphere color
    
    cena.add_light(new ambient_light(0.2)); //ambient_light with intensity of 0.2
    cena.add_light(new point_light(0.6, vp(2, 1, 0))); //point_light with intensity of 0.6 and with position(2, 1, 0)
    cena.add_light(new direction_light(0.2, vp(1, 4, 4))); //direction_light with intensity 0.2 with direction(1, 4, 4)
     
    cena.draw_scenario(); //Execute the ray tracing

    cena.save_scenario("sphere.png"); //Save image in "sphere.png"

    return 0;
}
