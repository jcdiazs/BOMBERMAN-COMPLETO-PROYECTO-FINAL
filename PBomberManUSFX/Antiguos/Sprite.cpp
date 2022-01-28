#include "Sprite.h"


Sprite::Sprite(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
{
    //texture = _texture;
    this->texture = _texture;
    this->renderer = _renderer;

    // get width and height of texture;
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    // set clip and rect
    clip.x = 0;
    clip.y = 0;
    clip.w = width;
    clip.h = height;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
}


void Sprite::setSize(const int _width, const int _height)
{
    rect.w = _width;  // controls the width of the rect
    rect.h = _height; // controls the height of the rect
}

void Sprite::setPosition(const int _x, const int _y)
{
    rect.x = _x; // controls the rect's x coordinate
    rect.y = _y; // controls the rect's y coordinate
}

void Sprite::setClip(const int _width, const int _height, const int _x, const int _y)
{
    clip.w = _width;  // controls the width of the rect
    clip.h = _height; // controls the height of the rect
    clip.x = _x;      // controls the rect's x coordinate
    clip.y = _y;      // controls the rect's y coordinate
}

void Sprite::attachToCamera(bool _isAttached /* = true*/)
{
    this->isAttachedToCamera = _isAttached;
}

int Sprite::getWidth() const
{
    return rect.w;
}

int Sprite::getHeight() const
{
    return rect.h;
}

int Sprite::getPositionX() const
{
    return rect.x;
}

int Sprite::getPositionY() const
{
    return rect.y;
}

const SDL_Rect& Sprite::getRect() const
{
    return rect;
}

void Sprite::setFlip(SDL_RendererFlip _flip)
{
    flipping = _flip;
}

void Sprite::addAnimation(std::shared_ptr<Animation> _animation)
{
    animations.push_back(_animation);
}

void Sprite::update(const unsigned int _delta)
{
    for (auto& animation : animations)
    {
        animation->update(_delta);
    }
}


void Sprite::render(const SDL_Rect& _camera) const
{
    if (renderer != nullptr && texture != nullptr)
    {
        // change position according to camera
        SDL_Rect destrinationRect = rect;
        if (isAttachedToCamera)
        {
            destrinationRect.x -= _camera.x;
            destrinationRect.y -= _camera.y;
        }
        // draw on the screen
        SDL_RenderCopyEx(renderer, texture.get(), &clip, &destrinationRect, 0, nullptr, flipping);
    }
}