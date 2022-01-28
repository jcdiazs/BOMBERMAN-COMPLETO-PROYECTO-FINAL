#pragma once
#include "GameActor.h"
class Soil :
    public GameActor
{
public:
    Soil(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    virtual void update(const unsigned int delta) override;

};

