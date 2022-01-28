#include "WallBrick.h"
#include "../Const.h"

WallBrick::WallBrick(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
    : Wall(_texture, _renderer)
{
   
}

void WallBrick::update(const unsigned int delta)
{
    Wall::update(delta);
}