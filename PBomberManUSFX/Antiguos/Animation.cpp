#include "Animation.h"

#include "Sprite.h"

void Animation::addAnimationEntity(AnimationEntity _entity)
{
    animation.push_back(std::move(_entity));
    //animation.push_back(entity);
}

void Animation::setSprite(Sprite* _sprite)
{
    this->sprite = _sprite;
    //sprite = _sprite;

    if(!animation.empty())
    {
        AnimationEntity entity = animation[0];
        this->sprite->setClip(static_cast<int>(entity.width), static_cast<int>(entity.height),
                                static_cast<int>(entity.positionX), static_cast<int>(entity.positionY));
    }
}

void Animation::setAnimationInterval(const unsigned int _timeInMs)
{
    interval = _timeInMs;
}

void Animation::play()
{
    if(isPlaying)
        return;

    isPlaying = true;
    time = interval;
}

void Animation::pause()
{
    isPlaying = false;
}

void Animation::reset()
{
    pause();
    currentEntity = 0;
    time = 0;
}

void Animation::update(const unsigned int _delta)
{
    if(animation.size() < 1 || !sprite || !isPlaying)
        return;

    time += _delta;
    if(time >= interval)
    {
        time = 0;
        AnimationEntity entity = animation[currentEntity];
        currentEntity = (currentEntity + 1) % animation.size();
        sprite->setClip(static_cast<int>(entity.width), static_cast<int>(entity.height),
                        static_cast<int>(entity.positionX), static_cast<int>(entity.positionY));
    }
}
