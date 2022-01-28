#pragma once
#include "GameActor.h"
class MuroMetal :
    public GameActor
{
public:
    MuroMetal(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual);
    void setTileActual(Tile* _tileNuevo);
};

