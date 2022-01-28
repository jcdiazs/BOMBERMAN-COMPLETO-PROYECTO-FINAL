#pragma once
#include "Enemy.h"
#include "../GameTextures.h"

class PersonalizadoEnemy :
    public Enemy
{
public:
    PersonalizadoEnemy(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer);
};