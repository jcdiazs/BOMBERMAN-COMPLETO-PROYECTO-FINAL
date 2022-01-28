#include "WallPacmanAdapter.h"
#include "../Const.h"

bool WallPacmanAdapter::clipsCreated = initiliceClips();
//TileGraph* WallPacmanAdapter::tileGraph = new TileGraph(25, 15);

WallPacmanAdapter::WallPacmanAdapter(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tile)
    : GameActor(_texture, _renderer), WallPacman(_tile, loadWallTexture())
{
    //Texture::Renderer = _renderer;
    // movement animation
    //wallTexture->SetSDLTexture(_texture.get());
    //cout << "Aqui mismo" << endl;
  /*  movement = std::make_shared<Animation>();
    movement->addAnimationEntity(AnimationEntity(0, 0, tileSize, tileSize));
    movement->addAnimationEntity(AnimationEntity(tileSize * 1, 0, tileSize, tileSize));
    movement->addAnimationEntity(AnimationEntity(tileSize * 2, 0, tileSize, tileSize));
    movement->addAnimationEntity(AnimationEntity(tileSize * 3, 0, tileSize, tileSize));
    movement->addAnimationEntity(AnimationEntity(tileSize * 4, 0, tileSize, tileSize));
    movement->addAnimationEntity(AnimationEntity(tileSize * 5, 0, tileSize, tileSize));
    movement->addAnimationEntity(AnimationEntity(tileSize * 6, 0, tileSize, tileSize));
    movement->addAnimationEntity(AnimationEntity(tileSize * 7, 0, tileSize, tileSize));
    movement->setSprite(this);
    addAnimation(movement);*/
}

void WallPacmanAdapter::update(const unsigned int delta)
{
    Update();
    //GameActor::update(delta);
}

void WallPacmanAdapter::render(const SDL_Rect& camera)
{
    Render();
}
