#ifndef _BOMBERMAN_SCENES_GAME_OVER_SCENE_H_
#define _BOMBERMAN_SCENES_GAME_OVER_SCENE_H_

#include <SDL.h>
#include <memory>

#include "../Entities/Text.h"
#include "../Scenes/Scene.h"

/**
    * @brief GameManager Over Scene
    *
    */
class GameOverScene : public Scene
{
    public:
    /**
        * @brief Construct a new GameManager Over Scene
        *
        * @param game
        */
    GameOverScene(GameManager* _gameManager);
    /**
        * @brief Trigger on update if scene is active
        *
        * @param delta - time in milliseconds
        */
    virtual void update(const unsigned int delta) override;

    private:
    // timer until switch to next menu
    int untilNextSceneTimer = 0;
    // const
    const int sceneTimer = 2000;
};

#endif // _BOMBERMAN_SCENES_GAME_OVER_SCENE_H_
