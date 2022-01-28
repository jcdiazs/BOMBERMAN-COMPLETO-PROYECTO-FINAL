#ifndef _BOMBERMAN_ENTITIES_ENEMY_H_
#define _BOMBERMAN_ENTITIES_ENEMY_H_

#include <utility>

#include "../Entities/GameActor.h"
#include "../GameAITypes.h"

/**
    * @brief AI types for enemies
    *
    */
//enum class AIType : int
//{
//    Wandering,
//    Chasing
//};
/**
    * @brief Enemy class
    *
    */
class Enemy : public GameActor
{
    public:
    /**
        * @brief Create Enemy
        *
        */
    Enemy(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    /**
        * @brief Move enemy to specified position
        *
        * @param x - position X
        * @param y - position Y
        */
    void moveTo(const int x, const int y);
    /**
        * @brief Move enemy for specified diff of cells
        *
        * @param pathToCell - pair of number of cells on X and Y
        */
    void moveToCell(std::pair<int, int> pathToCell);
    /**
        * @brief Return is enemy moving to cell or not
        *
        * @return true - moving to cell
        * @return false - not moving to cell
        */
    bool isMovingToCell() const;
    /**
        * @brief Can enemy attack
        *
        * @return true - enemy can attack player
        * @return false - can't attack
        */
    bool canAttack() const;
    /**
        * @brief Get the Attack Radius of enemy
        *
        * @return int - attack radius
        */
    int getAttackRadius() const;
    /**
        * @brief Set AI type
        *
        * @param type - AI type
        */
    void setAIType(AIType type);
    /**
        * @brief Update movement of enemy
        *
        * @param delta - time in milliseconds
        */
    virtual void update(const unsigned int delta) override;
    /**
        * @brief Generate new path if enemy finish movement
        *
        */
    void generateNewPath();

    private:
    /**
        * @brief update movement of enemy
        *
        * @param delta - time in milliseconds
        */
    void updateMovement(const unsigned int delta);

    // movement
    int newPositionX = 0;      // position X to move
    int newPositionY = 0;      // position Y to move
    bool movingToCell = false; // is moving to cell
    std::pair<int, int> path;  // diff of cells to move
    // AI
    AIType aiType = AIType::wandering; // AI type
    // consts
    const float baseSpeed = 0.0018f;    // speed of enemy
    const float attackSpeed = 0.0025f;   // speed of attack enemy
    const int attackRadius = 4;         // attack radius (in cells)
    // animations
    std::shared_ptr<Animation> movement; // movement animation
};

#endif // _BOMBERMAN_ENTITIES_ENEMY_H_
