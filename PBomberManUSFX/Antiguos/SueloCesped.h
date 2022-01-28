#pragma once
#include "GameActor.h"
class SueloCesped :
    public GameActor
{
public:
    SueloCesped(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual);
    void setTileActual(Tile* _tileNuevo);
};

