#ifndef SDL_ENGINE_H
#define SDL_ENGINE_H

#include <iostream>
#include <cstring>
#include "scene.hpp"

#include <SDL2/SDL.h>

/*! \file SDLEngine.h
 *  \brief Engine em C++.
 *
 *  Engine em C++ utilizando SDL2.
*/

// \cond
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define R_MASK 0xff000000
    #define G_MASK 0x00ff0000
    #define B_MASK 0x0000ff00
    #define A_MASK 0x000000ff
#else
    #define R_MASK 0x000000ff
    #define G_MASK 0x0000ff00
    #define B_MASK 0x00ff0000
    #define A_MASK 0xff000000
#endif

#define SHIFT_RED   << 0
#define SHIFT_GREEN << 8
#define SHIFT_BLUE  << 16
#define SHIFT_ALPHA  << 24

// \endcond

//*******************************************************************
//*******************************************************************

/*!
 * Enum para comportamento da imagem na janela
*/
enum StretchCanvas
{
    NO_STRETCH,    //!< A imagem não é esticada
    FULL,          //!< A imagem é esticada até caber totalmente na janela
    LARGER_BORDER, //!< A imagem é esticada em relação a maior borda do canvas, preservando a proporção da imagem
    SMALLER_BORDER //!< A imagem é esticada em relação a menor borda do canvas, preservando a proporção da imagem
};

//*******************************************************************
//*******************************************************************

/*!
 * \brief Gerencia o SDL2
 *
 * Classe responsável por gerenciar o SDL2
*/
class SDLEngine {
    SDL_Window *_window;          //!< Janela
    SDL_Surface *_surfaceScreen;  //!< Surface da janela, onde contém a imagem que é printada
    SDL_Surface *_surfaceCanvas;  //!< Surface do canvas, copiara a imagem para o surface da janela

    SDL_Rect *_rectScreen;        //!< Informações de proporção da janela
    SDL_Rect *_rectCanvas;        //!< Informações de proporção do canvas
    SDL_Rect _imagem;             //!< Informações de proporção da imagem

    uint *_canvas;                //!< Array que contém a imagem
    uint _quantidadePix;          //!< Quantidade de pix que tem na imagem
    uint alturaCanvas, larguraCanvas;

    StretchCanvas _scretchCanvas; //!< Padrão que o canvas irá se esticar na janela

public:
    SDL_Rect imagemTamanho;       //!< Informações de proporção da imagem
                                  //!< 
                                  //!< É possível utilizar campos w e h para obter respectivamente a largura e a altura da imagem renderizada.
                                  //!<
                                  //!< Mais informações ver na documentação <a href='https://wiki.libsdl.org/SDL_Rect'>SDL_Rect</a>
    
    /*!
     * Inicializa o SDL e cria a janela que mostrará a imagem renderizada.
     * 
     * \param nomeJanela    Nome que a janela terá ao ser criada
     * \param larguraJanela Largura da janela
     * \param alturaJanela  Altura da janela
     * \param larguraCanvas Largura do canvas
     * \param alturaCanvas  Altura do canvas
     * \param flags         flags para a janela. Os valores podem ser:
     * \n ::SDL_WINDOW_FULLSCREEN
     * \n ::SDL_WINDOW_OPENGL
     * \n ::SDL_WINDOW_HIDDEN
     * \n ::SDL_WINDOW_BORDERLESS
     * \n ::SDL_WINDOW_RESIZABLE
     * \n ::SDL_WINDOW_MAXIMIZED
     * \n ::SDL_WINDOW_MINIMIZED
     * \n ::SDL_WINDOW_INPUT_GRABBED
     * \n ::SDL_WINDOW_ALLOW_HIGHDPI
     * \n ::SDL_WINDOW_VULKAN
     * \n Mais informações ver na documentação <a href='https://wiki.libsdl.org/SDL_WindowFlags'>SDL_WindowFlags</a>
     * \param scretchCanvas: Como a imagem se ajustará na tela. Os valores podem ser:
     * \n ::NO_STRETCH
     * \n ::FULL
     * \n ::LARGER_BORDER
     * \n ::SMALLER_BORDER
    */
    SDLEngine( const char *nomeJanela
             , uint larguraJanela, uint alturaJanela
             , uint larguraCanvas, uint alturaCanvas
             , uint flags = SDL_WINDOW_SHOWN
             , StretchCanvas scretchCanvas = StretchCanvas::NO_STRETCH );
    
    /*!
     *  Destroi o objeto, liberando a memória e desligando o SDL.
    */
    ~SDLEngine ();

    /*!
     * Atualiza as cores do canvas
     *
     * \param novoCanvas Array com as novas cores do canvas, com cada valor variando de 0 a 1
    */
    void atualizarCanvas(scene &cena, object* o = nullptr);

    /*!
     * Muda a regra de stretch
     *
     * \param scretch Nova regra de stretch
    */
    void mudarStretch ( StretchCanvas scretch );

    /*!
     * Muda as proporções do canvas
     *
     * \param novaLargura Nova lagura do canvas
     * \param novaAltura Nova altura do canvas
    */
    void mudarCanvas ( uint novaLargura, uint novaAltura );

    /*!
     * Verifica se houve algum evento de mudança de tamanho da janela e atualiza as informações da surface da janela caso haja o evento
     *
     * \param event <a href='https://wiki.libsdl.org/SDL_Event'>SDL_Event</a> que informará se houve o evento de mudança de tamanho da janela 
    */
    void junelaMudouTamanho ( const SDL_Event &event );

    /*!
     *  Atualiza a janela
    */
    void atualizarJanela ();

private:
    
    /*!
     *  Preenche as informações de largura e altura do SDL_Rect para que a imagem preencha toda a largura sem perder a proporção
    */
    void stretchProporcaoLargura ();

    /*!
     *  Preenche as informações de largura e altura do SDL_Rect para que a imagem preencha toda a altura sem perder a proporção
    */
    void stretchProporcaoAltura ();

    /*!
     *  Calcula as proporções da imagem
    */
    void atualizarProporcaoImagem ();

    /*!
     *  Faz a cópia da imagem do canvas para a janela de acordo com a regra de stretch indicada
    */
    void copiarCanvas ();

    /*!
     *  Atualiza as informações do surface da janela
    */
    void atualizarJanelaSurface ();
};

#endif
