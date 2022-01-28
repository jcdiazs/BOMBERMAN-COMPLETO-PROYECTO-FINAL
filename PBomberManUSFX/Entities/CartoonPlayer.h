#pragma once
#include "Player.h"
class CartoonPlayer :
    public Player
{
public:
    CartoonPlayer(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer);
};

