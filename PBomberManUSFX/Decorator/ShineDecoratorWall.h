#pragma once
#include "DecoratorWall.h"
class ShineDecoratorWall :
    public DecoratorWall
{
public:
    ShineDecoratorWall(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer, GameActor* _wall) :DecoratorWall(texture, renderer, _wall) {};
    void render(const SDL_Rect& _camera);
};

