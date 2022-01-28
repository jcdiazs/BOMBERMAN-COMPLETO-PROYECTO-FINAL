#include <string>

#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/MenuScene.h"

GameOverScene::GameOverScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // gameManager over text
    auto gameOverText =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "GAME OVER");
    gameOverText->setSize(static_cast<int>(gameManager->getWindowWidth() / 3.0f),
                            static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    gameOverText->setPosition(
        static_cast<int>(gameManager->getWindowWidth() / 2.0f - gameOverText->getWidth() / 2.0f),
        static_cast<int>(gameManager->getWindowHeight() / 2.0f - gameOverText->getHeight() / 2.0f));
    addObject(gameOverText);
}

void GameOverScene::update(const unsigned int delta)
{
    untilNextSceneTimer += delta;
    if(untilNextSceneTimer >= sceneTimer)
    {
        untilNextSceneTimer = 0;
        gameManager->getSceneManager()->activateScene("inicio");
    }
}
