#include <string>

#include "../GameManager.h"
#include "../Scenes/LevelScene.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/StageScene.h"

StageScene::StageScene(GameManager* _gameManager, const unsigned int _level, const unsigned int _score)
    : Scene(_gameManager), stage(_level), score(_score)
{
    // stage text
    auto text = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(),
                                        "Nivel " + std::to_string(_level));
    text->setSize(static_cast<int>(gameManager->getWindowWidth() / 3.0f),
                    static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    text->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - text->getWidth() / 2.0f),
                        static_cast<int>(gameManager->getWindowHeight() / 2.0f - text->getHeight() / 2.0f));
    addObject(text);
}

StageScene::StageScene(GameManager* _gameManager, Skin _skin, const unsigned int _level, const unsigned int _score)
    : Scene(_gameManager), skin (_skin), stage(_level), score(_score)
{
    // stage text
    auto text = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(),
        "Nivel " + std::to_string(_level));
    text->setSize(static_cast<int>(gameManager->getWindowWidth() / 3.0f),
        static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    text->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - text->getWidth() / 2.0f),
        static_cast<int>(gameManager->getWindowHeight() / 2.0f - text->getHeight() / 2.0f));
    addObject(text);
}



void StageScene::update(const unsigned int _delta)
{
    untilNextSceneTimer += _delta;
    if(untilNextSceneTimer >= sceneTimer)
    {
        untilNextSceneTimer = 0;
        gameManager->getSceneManager()->addScene("level", std::make_shared<LevelScene>(gameManager, skin, stage, score));
        gameManager->getSceneManager()->activateScene("level");
        gameManager->getSceneManager()->removeScene("stage");
    }
}
