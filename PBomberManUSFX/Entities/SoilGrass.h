#pragma once
#include "Soil.h"
class SoilGrass :
    public Soil
{
public:
    SoilGrass(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    virtual void update(const unsigned int delta) override;
};


