#pragma once
#include "Enemy.h"
#include "../GameTextures.h"

class ClasicoEnemy :
    public Enemy
{
public:
    ClasicoEnemy(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer);
};

