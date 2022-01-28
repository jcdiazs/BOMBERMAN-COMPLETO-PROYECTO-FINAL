#include <utility>

#include "../Entities/GameActor.h"
#include "../GameAITypes.h"


class Item : public GameActor
{
public:
    /**
        * @brief Create Enemy
        *
        */
    Item(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
    /**
        * @brief Move enemy to specified position
        *
        * @param x - position X
        * @param y - position Y
        */
    
  
    int getAttackRadius() const;
    /**
        * @brief Set AI type
        *
        * @param type - AI type
        */
    


private:
   
    const float attackSpeed = 0.0025f;   // speed of attack enemy
    const int attackRadius = 4;         // attack radius (in cells)
    // animations

};


