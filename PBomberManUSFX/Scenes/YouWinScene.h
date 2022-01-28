#include <SDL.h>
#include <memory>

#include "../Entities/Text.h"
#include "../Scenes/Scene.h"


class YouWinScene : public Scene
{
public:
    
    YouWinScene(GameManager* _gameManager);
    
    virtual void update(const unsigned int delta) override;

private:
    // timer until switch to next menu
    int untilNextSceneTimer = 0;
    // const
    const int sceneTimer = 2000;
};