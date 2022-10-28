#include "../header/SDLEngine.hpp"
#include "../header/px.hpp"

SDLEngine::SDLEngine( const char *nomeJanela
                    , uint larguraJanela, uint alturaJanela
                    , uint larguraCanvas, uint alturaCanvas
                    , uint flags
                    , StretchCanvas scretchCanvas )
: _canvas( nullptr )
, _scretchCanvas( scretchCanvas )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "SDL não conseguiu inicializar! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        _window = SDL_CreateWindow( nomeJanela
                                 , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
                                 , larguraJanela, alturaJanela
                                 , flags );
        if ( _window == nullptr )
        {
            std::cerr << "Não foi possível criar a janela! SDL_Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            atualizarJanelaSurface();

            mudarCanvas( larguraCanvas, alturaCanvas );

            mudarStretch( _scretchCanvas );
        }
    }
}

//*******************************************************************
//*******************************************************************

SDLEngine::~SDLEngine ()
{
    SDL_FreeSurface( _surfaceScreen );
    SDL_FreeSurface( _surfaceCanvas );
    SDL_DestroyWindow( _window );
    SDL_Quit();

    if ( _canvas != nullptr)
        delete [] _canvas;
}

//*******************************************************************
//*******************************************************************

void SDLEngine::atualizarCanvas(scene &cena){
    for(int i = 0, px_position = 0; i < alturaCanvas; i++){
        for(int j = 0; j < larguraCanvas; j++, px_position++){
            px pixel = cena.get_pixel(i, j);
            _canvas[px_position] = ( ( (uint)(pixel.convert_red()) SHIFT_RED )   & R_MASK )
                   + ( ( (uint)(pixel.convert_green()) SHIFT_GREEN ) & G_MASK )
                   + ( ( (uint)(pixel.convert_blue()) SHIFT_BLUE )  & B_MASK )
                   + A_MASK;
        }
    }
    copiarCanvas();
}

//*******************************************************************
//*******************************************************************

void SDLEngine::mudarStretch ( StretchCanvas scretch )
{
    _scretchCanvas = scretch;
    SDL_FillRect( _surfaceScreen, nullptr, A_MASK );
    atualizarProporcaoImagem();
    copiarCanvas();
}

//*******************************************************************
//*******************************************************************

void SDLEngine::mudarCanvas ( uint novaLargura, uint novaAltura )
{
    if ( _canvas != nullptr )
    {
        SDL_FreeSurface( _surfaceCanvas );
        delete [] _canvas;
    }
    this->larguraCanvas = novaLargura;
    this->alturaCanvas = novaAltura;
    _quantidadePix = novaLargura * novaAltura;

    _canvas = new uint[_quantidadePix];
    _surfaceCanvas = SDL_CreateRGBSurfaceFrom( _canvas
                                             , novaLargura, novaAltura
                                             , 32, 4 * novaLargura
                                             , R_MASK, G_MASK, B_MASK, A_MASK );
    _rectCanvas = &( _surfaceCanvas->clip_rect );
    atualizarProporcaoImagem();
}

//*******************************************************************
//*******************************************************************

void SDLEngine::atualizarJanela ()
{
    SDL_UpdateWindowSurface( _window );
}

//*******************************************************************
//*******************************************************************

void SDLEngine::junelaMudouTamanho ( const SDL_Event &event )
{
    if ( event.type == SDL_WINDOWEVENT )
    {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            atualizarJanelaSurface();
            SDL_FillRect( _surfaceScreen, nullptr, A_MASK );
            atualizarProporcaoImagem();
            copiarCanvas();
        }
    }
}

//*******************************************************************
//*******************************************************************

void SDLEngine::stretchProporcaoLargura ()
{
    _imagem.w = _rectScreen->w;
    _imagem.h = ( _rectScreen->w * _rectCanvas->h ) / _rectCanvas->w;
}

//*******************************************************************
//*******************************************************************

void SDLEngine::stretchProporcaoAltura ()
{
    _imagem.w = ( _rectScreen->h * _rectCanvas->w ) / _rectCanvas->h;
    _imagem.h = _rectScreen->h;
}

//*******************************************************************
//*******************************************************************

void SDLEngine::atualizarProporcaoImagem ()
{
    switch ( _scretchCanvas )
    {
        case StretchCanvas::NO_STRETCH:
            _imagem = *_rectCanvas;
            break;
        case StretchCanvas::FULL:
            _imagem = *_rectScreen;
            break;
        case StretchCanvas::SMALLER_BORDER:
            if ( _rectCanvas->w < _rectCanvas->h )      stretchProporcaoLargura();
            else if ( _rectCanvas->w > _rectCanvas->h ) stretchProporcaoAltura();
            else                                        _imagem = *_rectScreen;
            
            break;
        case StretchCanvas::LARGER_BORDER:
            if ( _rectCanvas->w > _rectCanvas->h )      stretchProporcaoLargura();
            else if ( _rectCanvas->w < _rectCanvas->h ) stretchProporcaoAltura();
            else                                        _imagem = *_rectScreen;
            
            break;
    }

    imagemTamanho = _imagem;
}

//*******************************************************************
//*******************************************************************

void SDLEngine::copiarCanvas ()
{
    SDL_Rect imgRect = _imagem;
    
    if ( _scretchCanvas == StretchCanvas::NO_STRETCH )
        SDL_BlitSurface( _surfaceCanvas, nullptr, _surfaceScreen, &imgRect );
    else
        SDL_BlitScaled( _surfaceCanvas, nullptr, _surfaceScreen, &imgRect );
    
}

void SDLEngine::atualizarJanelaSurface ()
{
    _surfaceScreen = SDL_GetWindowSurface( _window );
    _rectScreen = &(_surfaceScreen->clip_rect);
}
