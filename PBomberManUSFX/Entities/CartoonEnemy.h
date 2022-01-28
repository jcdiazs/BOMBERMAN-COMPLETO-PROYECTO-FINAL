#pragma once
#include "Enemy.h"
class CartoonEnemy :
    public Enemy
{
public:
    CartoonEnemy(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer);
};

