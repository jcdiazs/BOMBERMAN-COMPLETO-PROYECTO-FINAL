#include "WallStone.h"
#include "../Const.h"

WallStone::WallStone(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
    : Wall(_texture, _renderer)
{

}

void WallStone::update(const unsigned int delta)
{
    Wall::update(delta);
}

void WallStone::render(const SDL_Rect& camera)
{
    Wall::render(camera);
    //std::cout << "dentro de wallstone" << std::endl;

}
