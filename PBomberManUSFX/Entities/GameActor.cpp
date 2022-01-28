#include "../Entities/GameActor.h"

void GameActor::revertLastMove()
{
    setPosition(getPositionX() - prevPosDeltaX, getPositionY() - prevPosDeltaY);
}

void GameActor::setMoving(bool _moving)
{
    this->moving = _moving;
}

bool GameActor::isMoving() const
{
    return moving;
}
