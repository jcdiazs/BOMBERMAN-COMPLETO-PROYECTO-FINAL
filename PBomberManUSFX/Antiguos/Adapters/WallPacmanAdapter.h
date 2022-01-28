#pragma once
#include "../Entities/GameActor.h"
#include "../Adapters/WallPacman.h"
class WallPacmanAdapter :
    public GameActor, public WallPacman
{

public:
    WallPacmanAdapter(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    virtual void update(const unsigned int delta) override;
    virtual void render();
private:
    std::shared_ptr<Animation> movement; // movement animation
};

