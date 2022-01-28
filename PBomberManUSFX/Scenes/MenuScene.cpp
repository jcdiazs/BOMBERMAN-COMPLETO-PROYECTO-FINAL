#include <string>

#include "../Entities/Sprite.h"
#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/LevelScene.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/StageScene.h"

// ++increment for menu id
MenuItem& operator++(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) + 1);
    if(c == MenuItem::Last)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::None) + 1);
    return c;
}


// --decrement for menu id
MenuItem& operator--(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) - 1);
    if(c == MenuItem::None)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::Last) - 1);
    return c;
}

// increment++ for menu id
MenuItem operator++(MenuItem& c, int)
{
    MenuItem result = c;
    ++c;
    return result;
}

// decrement-- for menu id
MenuItem operator--(MenuItem& c, int)
{
    MenuItem result = c;
    --c;
    return result;
}

MenuScene::MenuScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // background
    auto background = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::Skins), gameManager->getRenderer());
    
    background->setPosition(0, 0);
    
    background->setSize(gameManager->getWindowWidth(),  gameManager->getWindowHeight());
    addObject(background);

    startPlayer1Text = std::make_shared<Text>(gameManager->getAssetManager()->getFont1(), gameManager->getRenderer(), "Josh");
    startPlayer1Text->setColor(colorPressed);
    startPlayer1Text->setSize(84.77, 24.71);
    startPlayer1Text->setPosition(105, 288.11);
    addObject(startPlayer1Text);

    startPlayer2Text = std::make_shared<Text>(gameManager->getAssetManager()->getFont1(), gameManager->getRenderer(), "The Classic One");
    startPlayer2Text->setColor(colorStandard);
    startPlayer2Text->setSize(302, 24.71);
    startPlayer2Text->setPosition(244.7, 288.11);
    addObject(startPlayer2Text);

    startPlayer3Text = std::make_shared<Text>(gameManager->getAssetManager()->getFont1(), gameManager->getRenderer(), "Tyler");
    startPlayer3Text->setColor(colorStandard);
    startPlayer3Text->setSize(103.77, 24.71);
    startPlayer3Text->setPosition(592, 288.11);
    addObject(startPlayer3Text);

    startPlayer4Text = std::make_shared<Text>(gameManager->getAssetManager()->getFont1(), gameManager->getRenderer(), "Bruno");
    startPlayer4Text->setColor(colorStandard);
    startPlayer4Text->setSize(105.18, 24.71);
    startPlayer4Text->setPosition(98, 541.11);
    addObject(startPlayer4Text);

    startPlayer5Text = std::make_shared<Text>(gameManager->getAssetManager()->getFont1(), gameManager->getRenderer(), "The King");
    startPlayer5Text->setColor(colorStandard);
    startPlayer5Text->setSize(160.77, 24.71);
    startPlayer5Text->setPosition(312, 541.11);
    addObject(startPlayer5Text);

    startPlayer6Text = std::make_shared<Text>(gameManager->getAssetManager()->getFont1(), gameManager->getRenderer(), "Jass");
    startPlayer6Text->setColor(colorStandard);
    startPlayer6Text->setSize(84.77, 24.71);
    startPlayer6Text->setPosition(600, 541.11);
    addObject(startPlayer6Text);

    // exit menu
    /*exitText = std::make_shared<Text>(gameManager->getAssetManager()->getFont1(), gameManager->getRenderer(), "SALIR");
    exitText->setSize(90, 24.71);
    exitText->setPosition(350,570);
    addObject(exitText);*/

    gameManager->getSceneManager()->addScene("gameover", std::make_shared<GameOverScene>(gameManager));
    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::MainMenu));
}

void MenuScene::onEnter()
{
    menuMusic->play();
}

void MenuScene::onExit()
{
    menuMusic->stop();
}

void MenuScene::onEvent(const SDL_Event& event)
{
    Scene::onEvent(event);
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.scancode)
        {
            // we should select next menu item
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                currentSelectedMenu++;
                onMenuItemSelect();
                break;
            // we should select prev menu item
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                currentSelectedMenu--;
                onMenuItemSelect();
                break;
            // enter in menu item
            case SDL_SCANCODE_SPACE:
            case SDL_SCANCODE_RETURN:
                onMenuItemPress();
                break;
            default:
                break;
        }
    }
}

void MenuScene::onMenuItemSelect()
{
    // reset menu items color
    startPlayer1Text->setColor(colorStandard);
    startPlayer2Text->setColor(colorStandard);
    startPlayer3Text->setColor(colorStandard);
    startPlayer4Text->setColor(colorStandard);
    startPlayer5Text->setColor(colorStandard);
    startPlayer6Text->setColor(colorStandard);

    /*exitText->setColor(colorStandard);*/

    // change color of selected menu item
    switch(currentSelectedMenu)
    {
        case MenuItem::StartPlayer1:
            startPlayer1Text->setColor(colorPressed);
            break;
        case MenuItem::StartPlayer2:
            startPlayer2Text->setColor(colorPressed);
            break;
        case MenuItem::StartPlayer3:
            startPlayer3Text->setColor(colorPressed);
            break;
        case MenuItem::StartPlayer4:
            startPlayer4Text->setColor(colorPressed);
            break;
        case MenuItem::StartPlayer5:
            startPlayer5Text->setColor(colorPressed);
            break;
        case MenuItem::StartPlayer6:
            startPlayer6Text->setColor(colorPressed);
            break;

        /*case MenuItem::Exit:
            exitText->setColor(colorPressed);
            break;*/
        default:
            break;
    }
}

void MenuScene::onMenuItemPress()
{
    switch(currentSelectedMenu)
    {
        case MenuItem::StartPlayer1:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, Skin::SKIN_JOSH, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;

        case MenuItem::StartPlayer2:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, Skin::SKIN_CLASSIC, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;

        case MenuItem::StartPlayer3:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, Skin::SKIN_TYLER, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;

        case MenuItem::StartPlayer4:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, Skin::SKIN_BRUNO, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;

        case MenuItem::StartPlayer5:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, Skin::SKIN_KING, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;

        case MenuItem::StartPlayer6:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, Skin::SKIN_JASS, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;
        
       /* case MenuItem::Exit:*/
            // stop gameManager loop
            /*gameManager->stop();*/
            ///*break;*/
        default:
            break;
    }
}
