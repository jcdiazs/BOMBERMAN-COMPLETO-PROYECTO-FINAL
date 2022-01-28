#ifndef _BOMBERMAN_ENTITIES_CREATURE_H_
#define _BOMBERMAN_ENTITIES_CREATURE_H_

#include "../Entities/Sprite.h"

/**
    * @brief GameActor class
    *
    */
class GameActor : public Sprite
{
    public:
    /**
        * @brief Create creature
        */
    using Sprite::Sprite;
    /**
        * @brief Revert last movement of creature
        *
        */
    void revertLastMove();
    /**
        * @brief Set creature to move
        *
        * @param isMoving - moving
        */
    void setMoving(bool isMoving);
    /**
        * @brief Is creature moving at this moment
        *
        * @return true - if moving
        * @return false - if idle
        */
    bool isMoving() const;

    protected:
    // for movement revert
    int prevPosDeltaX = 0;
    int prevPosDeltaY = 0;
    std::shared_ptr<Animation> movement;

    private:
    bool moving = false; // movement status
};

#endif // _BOMBERMAN_ENTITIES_CREATURE_H_
