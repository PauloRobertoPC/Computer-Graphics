#include "header/vp.hpp"
#include "header/px.hpp"
#include "header/viewport.hpp"
#include "header/canvas.hpp"
#include "header/sphere.hpp"
#include "header/scene.hpp"
#include "header/ambient_light.hpp"
#include "header/point_light.hpp"
#include "header/direction_light.hpp"
#include "header/spot_light.hpp"
#include "header/plan.hpp"
#include "header/matrix.hpp"
#include "header/cilinder.hpp"
#include "header/cone.hpp"
#include "header/mesh.hpp"
#include "header/cube.hpp"
#include "header/camera.hpp"
#include "header/SDLEngine.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <cmath>
#include <iostream>

#define LARGURA_TELA 500
#define ALTURA_TELA  500
#define LARGURA_CANVAS 500
#define ALTURA_CANVAS  500

using namespace std;

int main(){
    camera O(vp(0, 0, 0), vp(0, 0, -1), vp(1, 1, -1));
    viewport vw(40, 40, -20);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));

    scene cena(O, vw, c);

    cube* cuboa = new cube(px(1., 0.078, 0.576), px(1., 0.078, 0.576), px(1., 0.078, 0.576), 10);
    cuboa->mirror_xy();
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
    cubob->translation(vp(0, -50, -165));
    cubob->transform();
    cena.add_object(cubob);

    cena.add_object(new plan(vp(0, 0, -400), vp(0, 0, 1), px(0.5, 0.0, 0.5), px(0.5, 0.0, 0.5), px(0.5, 0.0, 0.5), 1));
    cena.add_object(new plan(vp(0, -250, 0), vp(0, 1, 0), px(0.0, 0.5, 0.0), px(0.0, 0.5, 0.0), px(0.0, 0.5, 0.0), 1));
    
    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    // cena.add_light(new point_light(px(0.7, 0.7, 0.7), vp(-100, 140, -20)));
    // cena.add_light(new direction_light(px(0.7, 0.7, 0.7), vp(0, -1, 0)));
    cena.add_light(new spot_light(px(0.7, 0.7, 0.7), vp(0, 1000, 0), vp(-1, -1, -1), 3.14/3.0));
     
    cena.draw_scenario(); //Execute the ray tracing

    cena.save_scenario("image.png"); //Save image in "image.png"

    //
    
    SDLEngine sdlEngine{ "IMAGEM", 
                        LARGURA_TELA, ALTURA_TELA, 
                        LARGURA_CANVAS, ALTURA_CANVAS
    };
    
    SDL_Event e;
    bool quit = false;
    bool teste = true;
    int testeNum = 0; 

    int press = 0, x, y, i, j;
    
    sdlEngine.atualizarCanvas( cena );
    sdlEngine.atualizarJanela();

    while (!quit){
        while(SDL_PollEvent(&e) ){
            if(e.type == SDL_QUIT) quit = true;
            if(SDL_MOUSEBUTTONDOWN == e.type){
                if(SDL_BUTTON_LEFT == e.button.button){
                    if(!press){
                        SDL_GetMouseState(&x, &y);
                        std::cout << "LEFT BUTTON PRESSED AT xy: " << x << " " << y << "\n";
                        press ^= 1;
                    }else{
                        SDL_GetMouseState(&i, &j);
                        std::cout << "LEFT BUTTON PRESSED AT ij: " << i << " " << j << "\n";
                        press ^= 1;
                        sdlEngine.atualizarCanvas( cena );
                        sdlEngine.atualizarJanela();
                    }
                }
            }
        }
        // std::cout << "AQUI\n";
    }
    
    return 0;
}
