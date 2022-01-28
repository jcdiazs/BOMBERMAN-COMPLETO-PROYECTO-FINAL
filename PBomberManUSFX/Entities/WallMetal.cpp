#include "WallMetal.h"
#include "../Const.h"

WallMetal::WallMetal(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
    : Wall(_texture, _renderer)
{
   
}

void WallMetal::update(const unsigned int delta)
{
    Wall::update(delta);
}