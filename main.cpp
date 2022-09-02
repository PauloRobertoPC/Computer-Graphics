#include <bits/stdc++.h>
#include "util.hpp"
#include "viewport.hpp"
#include "canvas.hpp"
#include "sphere.hpp"
#include "scene.hpp"

using namespace std;

int main(){
    double d = 5; //dJanela
    double rEsfera = 0.5; //rEsfera
    
    px background_color(100, 100, 100);
    vp O(0, 0, 0);
    viewport vw(2, 2, -d); //Vh, Vw, distancia
    canvas c(500, 500, vw, background_color); //Ch, Cw, viewport, background_color

    scene cena(O, vw, c); //cena

    cena.add_sphere(sphere(0, 0, -(d+rEsfera), rEsfera, px(255, 0, 0))); //esfera(x, y, z), raio, e cor da esfera
     
    cena.draw_scenario(); //Executa o ray tracing

    cena.save_scenario("esferas.png"); //Salva a imagem em "esfereras.png"
     
    return 0;
}
