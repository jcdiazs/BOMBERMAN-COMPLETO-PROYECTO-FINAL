#include "SoilGrass.h"
#include "../Const.h"

SoilGrass::SoilGrass(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
    : Soil(_texture, _renderer)
{

}

void SoilGrass::update(const unsigned int delta)
{
    Soil::update(delta);
}