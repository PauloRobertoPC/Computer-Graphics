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
#include "header/complex_object.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <cmath>
#include <iostream>
#include <sys/select.h>

#define LARGURA_TELA 500
#define ALTURA_TELA 500
#define LARGURA_CANVAS 500
#define ALTURA_CANVAS 500

using namespace std;

scene tarefa5()
{
    camera O(vp(0, 0, 0), vp(0, 0, -500), vp(600, 500, -665));
    viewport vw(60, 60, -20);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));
    scene cena(O, vw, c, PROJECTION::PERSPECITVE);

    cena.add_object(new sphere(vp(0, 95, -200), 5, px(0.854, 0.647, 0.125), px(0.854, 0.647, 0.125), px(0.854, 0.647, 0.125), 10));

    cube *cb = new cube("img/grass.jpg", 10);
    cb->scaling(vp(40, 40, 40));
    cb->transform();
    cb->translation(vp(0, -150, -165));
    cena.add_object(cb);

    cena.add_object(new cone(vp(0, -60, -200), vp(0., 1., 0), 90, 150, px(0., 1., 0.498), px(0., 1., 0.498), px(0., 1., 0.498), 10, false));
    cena.add_object(new cilinder(vp(0, -150, -200), vp(0., 1., 0), 5, 90, px(0.824, 0.706, 0.549), px(0.824, 0.706, 0.549), px(0.824, 0.706, 0.549), 10, true, true));

    cena.add_object(new plan(vp(0, -150, 0), vp(0, 1, 0), px(0.5, 0.5, 0.5), px(0.5, 0.5, 0.5), px(0.5, 0.5, 0.5), 1));
    cena.add_object(new plan(vp(200, -150, 0), vp(-1., 0., 0), px(0.686, 0.933, 0.933), px(0.686, 0.933, 0.933), px(0.686, 0.933, 0.933), 1));
    cena.add_object(new plan(vp(200, -150, -400), vp(0., 0., 1), px(0.686, 0.933, 0.933), px(0.686, 0.933, 0.933), px(0.686, 0.933, 0.933), 1));
    cena.add_object(new plan(vp(-200, -150, 0), vp(1., 0., 0.), px(0.933, 0.933, 0.933), px(0.933, 0.933, 0.933), px(00.933, 0.933, 0.933), 1));
    cena.add_object(new plan(vp(0, 150, 0), vp(0., -1., 0.), px(0.933, 0.933, 0.933), px(0.933, 0.933, 0.933), px(0.933, 0.933, 0.933), 1));

    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    cena.add_light(new point_light(px(0.7, 0.7, 0.7), vp(-100, 140, -20)));
    cena.add_light(new direction_light(px(0.3, 0.3, 0.3), vp(0, 0, 0)));

    return cena;
}

scene tarefa6()
{
    // camera O(vp(0, 0, 0), vp(0, 0, -1), vp(1, 1, -1));
    // camera O(vp(0, 800, -665), vp(0, 0, -665), vp(0, 800, -800)); // CIMA
    // camera O(vp(0, 0, 0), vp(0, 0, -165), vp(0, 90, -165)); // FRENTE
    // camera O(vp(600, 0, -665), vp(0, 0, -665), vp(600, 500, -665)); // SLA
    camera O(vp(665, 0, -665), vp(0, 0, -165), vp(665, 90, -665)); // DIREITA
    // viewport vw(60, 60, -20);
    viewport vw(1000, 1000, -20);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));

    // scene cena(O, vw, c, PROJECTION::PERSPECITVE);
    scene cena(O, vw, c, PROJECTION::PARALELL);

    // teto forro

    cube *left_roof = new cube(px(px::convert_rgb(214, 214, 214)), px(px::convert_rgb(214, 214, 214)), px(px::convert_rgb(214, 214, 214)), 10);
    cube *right_roof = new cube(px(px::convert_rgb(214, 214, 214)), px(px::convert_rgb(214, 214, 214)), px(px::convert_rgb(214, 214, 214)), 10);

    left_roof->scaling(vp(300, 50, 970));
    left_roof->shear_yx(0.75);
    left_roof->translation(vp(-150, 363, -665));

    right_roof->scaling(vp(300, 50, 970));
    right_roof->shear_yx(0.75);
    right_roof->translation(vp(-150, 363, -665));
    right_roof->mirror_yz();

    cena.add_object(left_roof);
    cena.add_object(right_roof);

    // teto frontal

    cube *front_left_roof = new cube(px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), 10);
    cube *front_right_roof = new cube(px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), 10);

    front_left_roof->scaling(vp(300, 50, 30));
    front_left_roof->shear_yx(0.75);
    front_left_roof->translation(vp(-150, 363, -165));

    front_right_roof->scaling(vp(300, 50, 30));
    front_right_roof->shear_yx(0.75);
    front_right_roof->translation(vp(-150, 363, -165));
    front_right_roof->mirror_yz();

    cena.add_object(front_left_roof);
    cena.add_object(front_right_roof);

    // teto traseiro

    cube *back_left_roof = new cube(px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), 10);
    cube *back_right_roof = new cube(px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), px(0.5882, 0.2941, 0), 10);

    back_left_roof->scaling(vp(300, 50, 30));
    back_left_roof->shear_yx(0.75);
    back_left_roof->translation(vp(-150, 363, -1165));

    back_right_roof->scaling(vp(300, 50, 30));
    back_right_roof->shear_yx(0.75);
    back_right_roof->translation(vp(-150, 363, -1165));
    back_right_roof->mirror_yz();

    cena.add_object(back_left_roof);
    cena.add_object(back_right_roof);

    // vigas frontais

    cube *front_left_beam = new cube(px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), 10);
    cube *front_right_beam = new cube(px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), 10);

    front_left_beam->scaling(vp(50, 500, 30));
    front_left_beam->translation(vp(-325, 0, -165));

    front_right_beam->scaling(vp(50, 500, 30));
    front_right_beam->translation(vp(325, 0, -165));

    cena.add_object(front_left_beam);
    cena.add_object(front_right_beam);

    // vigas traseiras

    cube *back_left_beam = new cube(px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), 10);
    cube *back_right_beam = new cube(px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), px(0.3725, 0.3058, 0.2784), 10);

    back_left_beam->scaling(vp(50, 500, 30));
    back_left_beam->translation(vp(-325, -0, -1165));

    back_right_beam->scaling(vp(50, 500, 30));
    back_right_beam->translation(vp(325, -0, -1165));

    cena.add_object(back_left_beam);
    cena.add_object(back_right_beam);

    // mesa

    cube *table = new cube(px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), 10);

    table->scaling(vp(250, 5, 150));
    table->translation(vp(0, -151, -665));

    cena.add_object(table);

    cube *left_suport = new cube(px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), 10);

    left_suport->scaling(vp(5, 95, 150));
    left_suport->translation(vp(-122.5, -202.5, -665));

    cena.add_object(left_suport);

    cube *right_suport = new cube(px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), 10);

    right_suport->scaling(vp(5, 95, 150));
    right_suport->translation(vp(122.5, -202.5, -665));

    cena.add_object(right_suport);

    // árvore de natal

    sphere *ball_tree = new sphere(vp(0, 50, -665), 4.5, px(1, 1, 0), px(1, 1, 0), px(1, 1, 0), 10);
    cena.add_object(ball_tree);

    cone *tree = new cone(vp(0, -100, -665), vp(0, 1, 0), 60, 150, px(px::convert_rgb(33, 112, 48)), px(px::convert_rgb(33, 112, 48)), px(px::convert_rgb(33, 112, 48)), 10, true);
    cena.add_object(tree);

    cilinder *suport_tree = new cilinder(vp(0, -140, -665), vp(0, 1, 0), 6, 40, px(px::convert_rgb(92, 79, 69)), px(px::convert_rgb(92, 79, 69)), px(px::convert_rgb(92, 79, 69)), 10, true, true);
    cena.add_object(suport_tree);

    cilinder *suport_tree_table = new cilinder(vp(0, -148, -665), vp(0, 1, 0), 30, 9, px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), 10, true, true);
    cena.add_object(suport_tree_table);

    plan *floor = new plan(vp(0, -255, -165), vp(0, 1, 0), "./img/grass.jpg", 10);
    cena.add_object(floor);

    plan *wall = new plan(vp(0, 0, -4000), vp(0, 0, 1), px(px::convert_rgb(126, 166, 253)), px(px::convert_rgb(126, 166, 253)), px(px::convert_rgb(126, 166, 253)), 10);
    cena.add_object(wall);

    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    cena.add_light(new point_light(px(1, 1, 0.7), vp(0, 1000, 0)));
    cena.add_light(new spot_light(px(1, 1, 0.7), vp(0, 380, -665), vp(0, -1, 0), 0.4));
    return cena;
}

scene cena_qualquer()
{
    camera O(vp(0, 0, 0), vp(0, 0, -1), vp(1, 1, -1));
    viewport vw(60, 60, -20);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));
    scene cena(O, vw, c, PROJECTION::PERSPECITVE);

    cube *cuboa = new cube(px(1., 0.078, 0.576), px(1., 0.078, 0.576), px(1., 0.078, 0.576), 10);
    cuboa->mirror_xy();
    cuboa->mirror_xy();
    cuboa->scaling(vp(100, 50, 50));
    cuboa->transform();
    cuboa->translation(vp(0.33, 103.29, -165));
    cuboa->translation(vp(0, 100, -165));
    cuboa->transform();
    cena.add_object(cuboa);

    // cubob->scaling(vp(100, 50, 50));
    // cubob->transform();
    // cubob->mirror_xy();
    // cubob->translation(vp(0, -50, -165));
    // cubob->transform();
    // cena.add_object(cubob);

    // cena.add_object(new plan(vp(0, 0, -400), vp(0, 0, 1), px(0.5, 0.0, 0.5), px(0.5, 0.0, 0.5), px(0.5, 0.0, 0.5), 1));
    // cena.add_object(new plan(vp(0, -250, 0), vp(0, 1, 0), px(0.0, 0.5, 0.0), px(0.0, 0.5, 0.0), px(0.0, 0.5, 0.0), 1));

    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    cena.add_light(new point_light(px(0.7, 0.7, 0.7), vp(-100, 140, -20)));
    cena.add_light(new direction_light(px(0.7, 0.7, 0.7), vp(0, -1, 0)));
    cena.add_light(new spot_light(px(0.7, 0.7, 0.7), vp(0, 1000, 0), vp(-1, -1, -1), 3.14 / 3.0));

    return cena;
}

scene fundo()
{
    // camera O(vp(0, 600, 0), vp(0, 0, 0), vp(0, 1050, -100)); // VISÃO DE CIMA
    camera O(vp(0, 300, 500), vp(0, 300, -425), vp(0, 1050, 0)); // VISÃO DE FRENTE
    viewport vw(60, 60, -20);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));
    scene cena(O, vw, c, PROJECTION::PERSPECITVE);

    cena.add_object(new cone(vp(0, 400, 200), vp(0., 1., 0), 20, 50, px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), 10, false));
    cena.add_object(new cilinder(vp(0, 450, 200), vp(0., 1., 0), 5, 90, px(px::convert_rgb(0, 0, 0)), px(px::convert_rgb(0, 0, 0)), px(px::convert_rgb(0, 0, 0)), 10, false, false));
    cena.add_object(new sphere(vp(0, 400, 200), 15, px(1, 1, 1), px(1, 1, 1), px(1, 1, 1), 10));

    cena.add_object(new cone(vp(0, 335, -425), vp(0., 1., 0), 10, 15, px(px::convert_rgb(206, 33, 35)), px(px::convert_rgb(206, 33, 35)), px(px::convert_rgb(206, 33, 35)), 10, false));
    cena.add_object(new cilinder(vp(0, 305, -425), vp(0., 1., 0), 10, 30, px(px::convert_rgb(206, 33, 35)), px(px::convert_rgb(206, 33, 35)), px(px::convert_rgb(206, 33, 35)), 10, false, false));

    cena.add_object(new cone(vp(40, 335, -425), vp(0., 1., 0), 10, 15, px(px::convert_rgb(219, 192, 32)), px(px::convert_rgb(219, 192, 32)), px(px::convert_rgb(219, 192, 32)), 10, false));
    cena.add_object(new cilinder(vp(40, 305, -425), vp(0., 1., 0), 10, 30, px(px::convert_rgb(219, 192, 32)), px(px::convert_rgb(219, 192, 32)), px(px::convert_rgb(219, 192, 32)), 10, false, false));

    cena.add_object(new cilinder(vp(80, 305, -425), vp(0., 1., 0), 10, 30, px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), 10, false, false));

    cube *prateleira = new cube(px(px::convert_rgb(54, 40, 34)), px(px::convert_rgb(54, 40, 34)), px(px::convert_rgb(54, 40, 34)), 10);
    prateleira->scaling(vp(500, 10, 50));
    prateleira->transform();
    prateleira->translation(vp(0, 300, -425));
    prateleira->transform();
    cena.add_object(prateleira);

    cena.add_object(new cilinder(vp(0, 180, -150), vp(0., 1., 0), 10, 30, px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), 10, false, false));
    cena.add_object(new cilinder(vp(190, 180, -150), vp(0., 1., 0), 10, 30, px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), 10, false, false));
    cena.add_object(new cilinder(vp(380, 180, -150), vp(0., 1., 0), 10, 30, px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), px(px::convert_rgb(78, 105, 26)), 10, false, false));

    cube *balcao = new cube(px(px::convert_rgb(82, 58, 40)), px(px::convert_rgb(82, 58, 40)), px(px::convert_rgb(82, 58, 40)), 10);
    balcao->scaling(vp(700, 160, 50));
    balcao->transform();
    balcao->translation(vp(200, 80, -150));
    balcao->transform();
    cena.add_object(balcao);

    cube *suporte_balcao = new cube(px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), 10);
    suporte_balcao->scaling(vp(700, 20, 100));
    suporte_balcao->transform();
    suporte_balcao->translation(vp(200, 170, -150));
    suporte_balcao->transform();
    cena.add_object(suporte_balcao);

    complex_object *banco1 = new complex_object("./objects/banco.obj", px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), 10);
    banco1->scaling(vp(100, 110, 100));
    banco1->translation(vp(0, 100, -10));
    cena.add_object(banco1);

    complex_object *banco2 = new complex_object("./objects/banco.obj", px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), 10);
    banco2->scaling(vp(100, 110, 100));
    banco2->translation(vp(190, 100, -10));
    cena.add_object(banco2);

    complex_object *banco3 = new complex_object("./objects/banco.obj", px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), px(px::convert_rgb(206, 179, 158)), 10);
    banco3->scaling(vp(100, 110, 100));
    banco3->translation(vp(380, 100, -10));
    cena.add_object(banco3);

    cube *tv_imagem = new cube("./img/tv.jpg", 10);
    tv_imagem->scaling(vp(20, 200, 250));
    tv_imagem->transform();
    tv_imagem->translation(vp(-499, 300, 0));
    tv_imagem->transform();
    cena.add_object(tv_imagem);

    cube *tv = new cube(px(px::convert_rgb(0, 0, 0)), px(px::convert_rgb(0, 0, 0)), px(px::convert_rgb(0, 0, 0)), 10);
    tv->scaling(vp(20, 220, 270));
    tv->transform();
    tv->translation(vp(-500, 300, 0));
    tv->transform();
    cena.add_object(tv);

    // complex_object *obj_chair = new complex_object("./objects/chair.obj", px(px::convert_rgb(116, 64, 0)), px(px::convert_rgb(116, 64, 0)), px(px::convert_rgb(116, 64, 0)), 10);
    // obj_chair->scaling(vp(200, 200, 200));
    // obj_chair->translation(vp(-340, 100, 150));
    // obj_chair->rotation_y(3.14 / 2);
    // cena.add_object(obj_chair);

    complex_object *obj = new complex_object("./objects/sla.obj", px(px::convert_rgb(124, 77, 46)), px(px::convert_rgb(124, 77, 46)), px(px::convert_rgb(124, 77, 46)), 10);
    obj->scaling(vp(150, 150, 250));
    obj->translation(vp(-425, 95, 0));
    cena.add_object(obj);

    // cone *tree = new cone(vp(-150, 110, 150), vp(0, 1, 0), 30, 70, px(px::convert_rgb(33, 112, 48)), px(px::convert_rgb(33, 112, 48)), px(px::convert_rgb(33, 112, 48)), 10, true);
    // cena.add_object(tree);

    // cilinder *suport_tree = new cilinder(vp(-150, 90, 150), vp(0, 1, 0), 3, 20, px(px::convert_rgb(92, 79, 69)), px(px::convert_rgb(92, 79, 69)), px(px::convert_rgb(92, 79, 69)), 10, true, true);
    // cena.add_object(suport_tree);

    // cilinder *suport_tree_table = new cilinder(vp(-150, 85, 150), vp(0, 1, 0), 15, 6, px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), px(px::convert_rgb(92, 63, 41)), 10, true, true);
    // cena.add_object(suport_tree_table);

    cena.add_object(new plan(vp(0, 0, 0), vp(0, 1, 0), "./img/floor.jpg", 1));
    cena.add_object(new plan(vp(500, 0, 0), vp(-1., 0., 0), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), 1));
    cena.add_object(new plan(vp(500, 0, -500), vp(0., 0., 1), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), 1));
    cena.add_object(new plan(vp(-500, 0, 0), vp(1., 0., 0.), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), 1));
    cena.add_object(new plan(vp(0, 500, 0), vp(0., -1., 0.), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), px(px::convert_rgb(78, 53, 36)), 1));

    cena.add_light(new ambient_light(px(0.3, 0.3, 0.3)));
    cena.add_light(new point_light(px(0.6, 0.6, 0.6), vp(0, 370, 200)));
    // cena.add_light(new direction_light(px(0.7, 0.7, 0.7), vp(0, -1, 0)));
    // cena.add_light(new spot_light(px(0.7, 0.7, 0.7), vp(0, 400, 150), vp(0, -1, 0), 0.7));
    cena.add_light(new spot_light(px(0.7, 0.7, 0.7), vp(0, 300, 200), vp(0, -1, 0), 0.5));

    return cena;
}

scene teste()
{
    camera O(vp(500, 0, -200), vp(0, -100, -1000), vp(500, 50, -200));
    viewport vw(60, 60, -20);
    canvas c(500, 500, px::convert_rgb(255, 255, 255));
    scene cena(O, vw, c, PROJECTION::PERSPECITVE);

    complex_object *obj = new complex_object("./objects/sla.obj", px(px::convert_rgb(255, 160, 20)), px(px::convert_rgb(255, 160, 20)), px(px::convert_rgb(255, 160, 20)), 10);
    obj->scaling(vp(150, 150, 150));
    obj->translation(vp(0, 0, -500));
    cena.add_object(obj);

    cena.add_light(new point_light(px(0.3, 0.3, 0.3), vp(0, 0, -500)));

    return cena;
}

int main()
{
    // scene cena = teste();
    scene cena = fundo();
    cena.draw_scenario(true);
    cena.save_scenario("image.png");

    // SDL2 stuffs

    SDLEngine sdlEngine{"IMAGEM",
                        LARGURA_TELA, ALTURA_TELA,
                        LARGURA_CANVAS, ALTURA_CANVAS};

    SDL_Event e;
    bool quit = false;
    bool teste = true;
    int testeNum = 0;
    object *choosen_object;
    light *choosen_light;

    set<object *> selecteds;

    int press = 0, x, y, i, j;

    sdlEngine.atualizarCanvas(cena, selecteds);
    sdlEngine.atualizarJanela();

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            if (SDL_MOUSEBUTTONDOWN == e.type)
            {
                if (SDL_BUTTON_LEFT == e.button.button)
                {
                    int op;
                    std::cout << " --- MENU DE OPCOES ---\n";
                    std::cout << "(1) - OBJETOS\n";
                    std::cout << "(2) - LUZES\n";
                    std::cout << "(3) - CÂMERA\n";
                    std::cout << "(4) - PROJEÇÃO\n";
                    std::cout << "(5) - RENDERIZAR\n";
                    cout << "Digite a sua opção: ";
                    cin >> op;

                    if (op == 1)
                    {
                        SDL_GetMouseState(&y, &x);
                        std::cout << "LEFT BUTTON PRESSED AT: " << x << " " << y << "\n";

                        choosen_object = cena.select_object(x, y);
                        if (choosen_object == nullptr)
                        {
                            std::cout << "NENHUM OBJETO SELECIONADO\n";
                            continue;
                        }
                        sdlEngine.atualizarCanvas(cena, selecteds, choosen_object);
                        sdlEngine.atualizarJanela();
                        int op;
                        std::cout << " --- MENU DE OPCOES ---\n";
                        std::cout << "(1) - Translação\n";
                        std::cout << "(2) - Rotação\n";
                        std::cout << "(3) - Espelhamento\n";
                        std::cout << "(4) - Escalonamento\n";
                        std::cout << "(5) - Cisalhamento\n";
                        std::cout << "(6) - Mudar Coloração\n";
                        std::cout << "(7) - Deletar\n";
                        std::cout << "(8) - Selecionar/Deselecionar Objetos\n";
                        cout << "Digite a sua opção: ";
                        cin >> op;
                        if (op == 1)
                        {
                            double i, j, k;
                            std::cout << "Digite o local de translação: ";
                            cin >> i >> j >> k;
                            for (object *o : selecteds)
                                o->translation(vp(i, j, k));
                        }
                        else if (op == 2)
                        {
                            std::cout << " --- MENU DE ROTAÇÕES ---\n";
                            std::cout << "(1) - Rotação no Eixo X\n";
                            std::cout << "(2) - Rotação no Eixo Y\n";
                            std::cout << "(3) - Rotação no Eixo Z\n";
                            // std::cout << "(4) - Rotação no Eixo Arbitrário\n";
                            cout << "Digite a sua opção: ";
                            cin >> op;
                            double angle;
                            std::cout << "Digite o ângulo da rotação(em radianos): ";
                            cin >> angle;
                            if (op == 1)
                            {
                                for (object *o : selecteds)
                                    o->rotation_x(angle);
                            }
                            else if (op == 2)
                            {
                                for (object *o : selecteds)
                                    o->rotation_y(angle);
                            }
                            else if (op == 3)
                            {
                                for (object *o : selecteds)
                                    o->rotation_z(angle);
                            }
                            else
                            {
                                // int i, j, k;
                                // std::cout << "Digite o ponto da origem do eixo: "; cin >> i >> j >> k; vp O(i, j, k);
                                // std::cout << "Digite o vetor direção do eixo: "; cin >> i >> j >> k; vp D(i, j, k);
                                // choosen_object->rotate_arbitrary(O, D, angle);
                            }
                        }
                        else if (op == 3)
                        {
                            std::cout << " --- MENU DE ESPELHAMENTO ---\n";
                            std::cout << "(1) - Espelhamento no plano XY\n";
                            std::cout << "(2) - Espelhamento no plano XZ\n";
                            std::cout << "(3) - Espelhamento no plano YZ\n";
                            std::cout << "(4) - Espelhamento no plano arbitrário\n";
                            cout << "Digite a sua opção: ";
                            cin >> op;
                            if (op == 1)
                            {
                                for (object *o : selecteds)
                                    o->mirror_xy();
                            }
                            else if (op == 2)
                            {
                                for (object *o : selecteds)
                                    o->mirror_xz();
                            }
                            else if (op == 3)
                            {
                                for (object *o : selecteds)
                                    o->mirror_yz();
                            }
                            else
                            {
                                double i, j, k;
                                std::cout << "Digite o vetor normal ao plano: ";
                                cin >> i >> j >> k;
                                vp n(i, j, k);
                                std::cout << "Digite o ponto que pertencem ao plano: ";
                                cin >> i >> j >> k;
                                vp p(i, j, k);
                                for (object *o : selecteds)
                                    o->mirror_arbitrary(n, p);
                            }
                        }
                        else if (op == 4)
                        {
                            double i, j, k;
                            std::cout << "Digite o tamanho do objeto: ";
                            cin >> i >> j >> k;
                            vp s(i, j, k);
                            for (object *o : selecteds)
                                o->scaling(s);
                        }
                        else if (op == 5)
                        {
                            std::cout << " --- MENU DE CISALHAMENTO ---\n";
                            std::cout << "(1) - Cisalhamento XY\n";
                            std::cout << "(2) - Cisalhamento YX\n";
                            std::cout << "(3) - Cisalhamento XZ\n";
                            std::cout << "(4) - Cisalhamento ZX\n";
                            std::cout << "(5) - Cisalhamento YZ\n";
                            std::cout << "(6) - Cisalhamento ZY\n";
                            cout << "Digite a sua opção: ";
                            cin >> op;
                            double angle;
                            std::cout << "Digite o ângulo do cisalhamento(em radianos): ";
                            cin >> angle;
                            if (op == 1)
                                for (object *o : selecteds)
                                    o->shear_xy(angle);
                            else if (op == 2)
                                for (object *o : selecteds)
                                    o->shear_yx(angle);
                            else if (op == 3)
                                for (object *o : selecteds)
                                    o->shear_xz(angle);
                            else if (op == 4)
                                for (object *o : selecteds)
                                    o->shear_zx(angle);
                            else if (op == 5)
                                for (object *o : selecteds)
                                    o->shear_yz(angle);
                            else
                                for (object *o : selecteds)
                                    o->shear_zy(angle);
                        }
                        else if (op == 6)
                        {
                            double i, j, k;
                            std::cout << "Digite as intensidades do ka: ";
                            cin >> i >> j >> k;
                            px ka(i, j, k);
                            std::cout << "Digite as intensidades do kd: ";
                            cin >> i >> j >> k;
                            px kd(i, j, k);
                            std::cout << "Digite as intensidades do ks: ";
                            cin >> i >> j >> k;
                            px ks(i, j, k);
                            for (object *o : selecteds)
                            {
                                o->set_k_a(ka);
                                o->set_k_d(kd);
                                o->set_k_s(ks);
                            }
                        }
                        else if (op == 7)
                        {
                            for (object *o : selecteds)
                                cena.del_object(o);
                        }
                        else
                        {
                            continue;
                        }
                        selecteds.clear();
                    }
                    else if (op == 2)
                    {
                        cena.print_lights();
                        cout << "Digite a sua opção: ";
                        cin >> op;

                        choosen_light = cena.select_light(op);
                        if (choosen_light == nullptr)
                        {
                            std::cout << "NENHUMA LUZ SELECIONADA\n";
                            continue;
                        }

                        std::cout << " --- MENU DE LUZES ---\n";
                        std::cout << "(1) - APAGAR\n";
                        std::cout << "(2) - ACENDER\n";
                        std::cout << "(3) - MUDAR INTENSIDADE\n";
                        std::cout << "(4) - MUDAR POSIÇÃO\n";
                        std::cout << "(5) - MUDAR ÂNGULO\n";
                        std::cout << "(6) - MUDAR DIREÇÃO\n";

                        cout << "Digite a sua opção: ";
                        cin >> op;

                        if (op == 1)
                        {
                            choosen_light->turn_off();
                        }
                        else if (op == 2)
                        {
                            choosen_light->turn_on();
                        }
                        else if (op == 3)
                        {
                            double i, j, k;
                            std::cout << "Digite a nova intensidade da luz: ";
                            cin >> i >> j >> k;
                            choosen_light->turn_on(px(i, j, k));
                        }
                        else if (op == 4)
                        {
                            double i, j, k;
                            std::cout << "Digite a nova posição: ";
                            cin >> i >> j >> k;
                            choosen_light->translation(vp(i, j, k));
                        }
                        else if (op == 5)
                        {
                            double angle;
                            std::cout << "Digite o novo ângulo: ";
                            cin >> angle;
                            choosen_light->change_angle(angle);
                        }
                        else if (op == 6)
                        {
                            double i, j, k;
                            std::cout << "Digite a nova direção: ";
                            cin >> i >> j >> k;
                            choosen_light->change_direction(vp(i, j, k));
                        }
                        else
                            continue;
                    }
                    else if (op == 3)
                    {
                        std::cout << " --- MENU DE CÂMERA ---\n";

                        std::cout << "(1) - MUDAR PARA CÂMERA\n";
                        std::cout << "(2) - MUDAR PARA MUNDO\n";
                        std::cout << "(3) - MUDAR VIEW (EYE, AT, UP)\n";
                        std::cout << "(4) - MUDAR TAMANHO DA JANELA\n";
                        std::cout << "(5) - MUDAR DISTÂNCIA FOCAL\n";
                        cout << "Digite a sua opção: ";
                        cin >> op;

                        if (op == 1)
                            cena.transform_scenario_to_camera();
                        else if (op == 2)
                            cena.transform_scenario_to_world();
                        else if (op == 3)
                        {
                            double i, j, k;
                            double a, b, c;
                            double l, m, n;
                            std::cout << "Digite as coordenadas do eye: ";
                            cin >> i >> j >> k;
                            std::cout << "Digite as coordenadas do at: ";
                            cin >> a >> b >> c;
                            std::cout << "Digite as coordenadas do up: ";
                            cin >> l >> m >> n;
                            cena.change_view(vp(i, j, k), vp(a, b, c), vp(l, m, n));
                        }
                        else if (op == 4)
                        {
                            double i, j;
                            std::cout << "Digite as novas medidas da janela (largura, altura): ";
                            cin >> i >> j;
                            cena.change_vp(i, j);
                        }
                        else if (op == 5)
                        {
                            double i;
                            std::cout << "Digite a nova distância focal: ";
                            cin >> i;
                            cena.change_d(i);
                        }
                    }
                    else if (op == 4)
                    {
                        std::cout << " --- MENU DE PROJEÇÕES ---\n";
                        std::cout << "(1) - PERSPECTIVA\n";
                        std::cout << "(2) - ORTOGRÁFICA\n";
                        cout << "Digite a sua opção: ";
                        cin >> op;

                        if (op == 1)
                        {
                            cena.change_projection(PROJECTION::PERSPECITVE);
                        }
                        else if (op == 2)
                        {
                            cena.change_projection(PROJECTION::PARALELL);
                        }
                        else
                            continue;
                    }
                    else if (op == 5)
                    {
                        cena.draw_scenario(false);
                    }
                    sdlEngine.atualizarCanvas(cena, selecteds);
                    sdlEngine.atualizarJanela();
                }
            }
        }
    }
    return 0;
}
