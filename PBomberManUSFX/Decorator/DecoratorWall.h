#pragma once
#include "../Entities/GameActor.h"
class DecoratorWall :
    public GameActor
{
private:
    GameActor* wall;
public:
    DecoratorWall(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer, GameActor* _wall):GameActor(texture, renderer) {
        wall = _wall;
    }
    
    void render(const SDL_Rect& _camera);
    
};

