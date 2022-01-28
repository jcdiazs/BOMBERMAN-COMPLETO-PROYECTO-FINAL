#pragma once
#include "GameActor.h"
class MuroCeramica :
    public GameActor
{
public:
    MuroCeramica(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual);
    void setTileActual(Tile* _tileNuevo);
    //void update(const unsigned int _delta);
};

