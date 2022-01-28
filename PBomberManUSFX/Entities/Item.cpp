#include "Item.h"

#include <chrono>
#include <functional>
#include <random>

#include "../Const.h"


Item::Item(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
    : GameActor(_texture, _renderer)
{
   
}


int Item::getAttackRadius() const
{
    return attackRadius * getWidth();
}

