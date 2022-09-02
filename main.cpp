#include <bits/stdc++.h>
#include "util.hpp"
#include "viewport.hpp"
#include "canvas.hpp"
#include "sphere.hpp"
#include "scene.hpp"
#include "light.hpp"

using namespace std;

int main(){
    px background_color = px::convert_rgb(255, 255, 255);
    vp O(0, 0, 0);
    viewport vw(1, 1, 1); //Vh, Vw, distancia
    canvas c(500, 500, vw, background_color); //Ch, Cw, viewport, background_color

    scene cena(O, vw, c); //cena

    
    cena.add_sphere(sphere(0, -1, 3, 1, px::convert_rgb(255, 0, 0))); //esfera(x, y, z), raio, e cor da esfera
    cena.add_sphere(sphere(2, 0, 4, 1, px::convert_rgb(0, 0, 255))); //esfera(x, y, z), raio, e cor da esfera
    cena.add_sphere(sphere(-2, 0, 4, 1, px::convert_rgb(0, 255, 0))); //esfera(x, y, z), raio, e cor da esfera
    cena.add_sphere(sphere(0, -5001, 0, 5000, px::convert_rgb(255, 255, 0))); //esfera(x, y, z), raio, e cor da esfera

    cena.add_light(light(ambient, 0.2));
    cena.add_light(light(point, 0.6, vp(2, 1, 0)));
    cena.add_light(light(directional, 0.2, vp(1, 4, 4)));
     
    cena.draw_scenario(); //Executa o ray tracing

    cena.save_scenario("esferas.png"); //Salva a imagem em "esfereras.png"

    return 0;
}
