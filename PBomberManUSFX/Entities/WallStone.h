#pragma once
#include "Wall.h"
class WallStone :
    public Wall
{
public:
    WallStone(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    virtual void update(const unsigned int delta) override;
    virtual void render(const SDL_Rect& camera);
    

};

