#pragma once

#include <vector>

class Sprite;
/**
    * @brief Animation part for clipping
    *
    */
struct AnimationEntity
{
    /**
        * @brief Construct a new Animation Entity object
        *
        * @param posX
        * @param posY
        * @param w
        * @param h
        */
    AnimationEntity(const unsigned int _posX, const unsigned int _posY, const unsigned int _w,
                    const unsigned int _h)
        : positionX(_posX), positionY(_posY), width(_w), height(_h){};

    unsigned int positionX = 0;
    unsigned int positionY = 0;
    unsigned int width = 0;
    unsigned int height = 0;
};

/**
    * @brief Animation class
    *
    */
class Animation
{
private:
    // animation
    std::vector<AnimationEntity> animation;
    unsigned int interval = 100;
    unsigned int time = 0;
    bool isPlaying = false;
    unsigned int currentEntity = 0;
    // sprite clipping
    Sprite* sprite = nullptr;

public:
    /**
        * @brief add entity
        *
        * @param entity
        */
    void addAnimationEntity(AnimationEntity _entity);
    /**
        * @brief Set the Sprite to animation for clipping
        *
        * @param sprite - sprite
        */
    void setSprite(Sprite* _sprite);
    /**
        * @brief Set the Animation Interval to change clipping
        *
        * @param timeInMs - time in ms
        */
    void setAnimationInterval(const unsigned int _timeInMs);
    /**
        * @brief play animation
        *
        */
    void play();
    /**
        * @brief pause animation
        *
        */
    void pause();
    /**
        * @brief reset animation and pause
        *
        */
    void reset();
    /**
        * @briefupdate animation
        *
        * @param delta
        */
    void update(const unsigned int _delta);

 
};
