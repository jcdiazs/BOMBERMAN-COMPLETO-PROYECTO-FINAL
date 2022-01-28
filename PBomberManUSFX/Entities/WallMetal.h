#pragma once
#include "Wall.h"
class WallMetal :
    public Wall
{
public:
    WallMetal(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    virtual void update(const unsigned int delta) override;
};

