#pragma once
#include "GameActor.h"
class Wall :
    public GameActor
{
public:
    Wall(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    virtual void update(const unsigned int delta) override;
    virtual void render(const SDL_Rect& camera);
};

