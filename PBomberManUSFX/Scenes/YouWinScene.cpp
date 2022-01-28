#include <string>

#include "../GameManager.h"
#include "../Scenes/YouWinScene.h"
#include "../Scenes/MenuScene.h"

YouWinScene::YouWinScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // gameManager over text
    auto YouWinSceneText =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "YOU WIN");
    YouWinSceneText->setSize(static_cast<int>(gameManager->getWindowWidth() / 3.0f),
        static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    YouWinSceneText->setPosition(
        static_cast<int>(gameManager->getWindowWidth() / 2.0f - YouWinSceneText->getWidth() / 2.0f),
        static_cast<int>(gameManager->getWindowHeight() / 2.0f - YouWinSceneText->getHeight() / 2.0f));
    addObject(YouWinSceneText);
}

void YouWinScene::update(const unsigned int delta)
{
    untilNextSceneTimer += delta;
    if (untilNextSceneTimer >= sceneTimer)
    {
        untilNextSceneTimer = 0;
        gameManager->getSceneManager()->activateScene("menu");
    }
}
