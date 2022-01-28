#pragma once
#include "Wall.h"
class WallBrick :
    public Wall
{
public:
    WallBrick(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    virtual void update(const unsigned int delta) override;
};

