#include "../Entities/GameGraphicObject.h"

GameGraphicObject::GameGraphicObject(SDL_Renderer* _renderer)
{
    this->renderer = _renderer;
}

GameGraphicObject::~GameGraphicObject() {}

void GameGraphicObject::setSize(const int width, const int height)
{
    rect.w = width;  // controls the width of the rect
    rect.h = height; // controls the height of the rect
}

void GameGraphicObject::setPosition(const int x, const int y)
{
    rect.x = x; // controls the rect's x coordinate
    rect.y = y; // controls the rect's y coordinate
}

void GameGraphicObject::setClip(const int width, const int height, const int x, const int y)
{
    clip.w = width;  // controls the width of the rect
    clip.h = height; // controls the height of the rect
    clip.x = x;      // controls the rect's x coordinate
    clip.y = y;      // controls the rect's y coordinate
}

void GameGraphicObject::attachToCamera(bool isAttached /* = true*/)
{
    this->isAttachedToCamera = isAttached;
}

int GameGraphicObject::getWidth() const
{
    return rect.w;
}

int GameGraphicObject::getHeight() const
{
    return rect.h;
}

int GameGraphicObject::getPositionX() const
{
    return rect.x;
}

int GameGraphicObject::getPositionY() const
{
    return rect.y;
}

const SDL_Rect& GameGraphicObject::getRect() const
{
    return rect;
}

void GameGraphicObject::setFlip(SDL_RendererFlip flip)
{
    flipping = flip;
}

void GameGraphicObject::update(const unsigned int /*delta*/) {}

void GameGraphicObject::render(const SDL_Rect& camera)
{
    if(renderer != nullptr && texture != nullptr)
    {
        // change position according to camera
        SDL_Rect destinationRect = rect;
        if(isAttachedToCamera)
        {
            destinationRect.x -= camera.x;
            destinationRect.y -= camera.y;
        }
        // render on the screen
        SDL_RenderCopyEx(renderer, texture.get(), &clip, &destinationRect, 0, nullptr, flipping);
    }
}