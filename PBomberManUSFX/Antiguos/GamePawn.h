#pragma once
#include "GameActor.h"
#include "./system/KeyboardInput.h"

class GamePawn :
    public GameActor
{
protected:
    KeyboardInput* keyboardInput;
    SDL_Keycode botonBomba = SDLK_b;
    SDL_Keycode botonArriba = SDLK_UP;
    SDL_Keycode botonAbajo = SDLK_DOWN;
    SDL_Keycode botonIzquierda = SDLK_LEFT;
    SDL_Keycode botonDerecha = SDLK_RIGHT;
    
public:
    // Constructores destructor
    GamePawn();
    GamePawn(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual);
    ~GamePawn();
    // Metodos accesores

    void setBotomBomba(SDL_KeyCode _botonBomba) { botonBomba = _botonBomba; }
    void setBotomArriba(SDL_KeyCode _botonArriba) { botonArriba = _botonArriba; }
    void setBotomAbajo(SDL_KeyCode _botonAbajo) { botonAbajo = _botonAbajo; }
    void setBotomDerecha(SDL_KeyCode _botonDerecha) { botonDerecha = _botonDerecha; }
    void setBotomIzquierda(SDL_KeyCode _botonIzquierda) { botonIzquierda = _botonIzquierda; }



    // Metodos heredados
    virtual void handleEvent(SDL_Event* _event){};
    virtual void render(SDL_Rect& _camara);
    virtual void update(const unsigned int delta);

    virtual void deleteGameObjet();

    // Metodos especificos
    virtual void setTileActual(Tile* _tileNuevo) {};

};

