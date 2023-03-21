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

scene ball_reflection()
{
    camera O(vp(0, 0, 0), vp(0, 0, 4), vp(0, 50, 0));
    viewport vw(60, 60, -60);
    canvas c(500, 500, px::convert_rgb(0, 0, 0));
    scene cena(O, vw, c, PROJECTION::PERSPECITVE);

    cena.add_object(new sphere(vp(0, -1, 3), 1, px(px::convert_rgb(255, 0, 0)), px(px::convert_rgb(255, 0, 0)), px(px::convert_rgb(255, 0, 0)), 500, 0.2));
    cena.add_object(new sphere(vp(2, 0, 4), 1, px(px::convert_rgb(0, 255, 0)), px(px::convert_rgb(0, 255, 0)), px(px::convert_rgb(0, 255, 0)), 10, 0.4));
    cena.add_object(new sphere(vp(-2, 0, 4), 1, px(px::convert_rgb(0, 0, 255)), px(px::convert_rgb(0, 0, 255)), px(px::convert_rgb(0, 0, 255)), 500, 0.3));
    cena.add_object(new sphere(vp(0, -5001, 0), 5000, px(px::convert_rgb(255, 255, 0)), px(px::convert_rgb(255, 255, 0)), px(px::convert_rgb(255, 255, 0)), 1000, 0.5));

    cena.add_light(new ambient_light(px(0.2, 0.2, 0.2)));
    cena.add_light(new point_light(px(0.6, 0.6, 0.6), vp(2, 1, 0)));
    cena.add_light(new direction_light(px(0.2, 0.2, 0, 2), vp(1, 4, 4)));

    return cena;
}

int main()
{
    // scene cena = teste();
    scene cena = ball_reflection();
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
                            std::cout << " --- MENU DE TRANSLAÇÕES ---\n";
                            std::cout << "(1) - Translação Ponto\n";
                            std::cout << "(2) - Translação Vetor\n";
                            cout << "Digite a sua opção: ";
                            cin >> op;
                            double i, j, k;
                            if (op == 1)
                            {
                                std::cout << "Digite o ponto de translação: ";
                                cin >> i >> j >> k;
                                for (object *o : selecteds)
                                    o->translation(vp(i, j, k));
                            }
                            else if (op == 2)
                            {
                                std::cout << "Digite o vetor de translação: ";
                                cin >> i >> j >> k;
                                for (object *o : selecteds)
                                    o->translation(vp(i, j, k), 0);
                            }
                            else
                            {
                                std::cout << "Opção Inválida\n";
                            }
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
                            std::cout << "Digite o ângulo da rotação(em graus): ";
                            cin >> angle;
                            angle = (angle * 3.141592) / 180;
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
                            std::cout << "Digite o ângulo do cisalhamento(em graus): ";
                            cin >> angle;
                            angle = (angle * 3.141592) / 180;
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
                            angle = (angle * 3.141592) / 180;
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
                        cena.save_scenario("image.png");
                    }
                    sdlEngine.atualizarCanvas(cena, selecteds);
                    sdlEngine.atualizarJanela();
                }
            }
        }
    }
    return 0;
}
