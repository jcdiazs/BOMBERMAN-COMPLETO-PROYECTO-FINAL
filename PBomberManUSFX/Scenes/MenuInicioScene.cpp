#include <string>

#include "../Entities/Sprite.h"
#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/LevelScene.h"
#include "../Scenes/MenuInicioScene.h"


// ++increment for menu id
MenuItemI& operator++(MenuItemI& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItemI>(static_cast<type>(c) + 1);
    if (c == MenuItemI::Last)
        c = static_cast<MenuItemI>(static_cast<type>(MenuItemI::None) + 1);
    return c;
}

// --decrement for menu id
MenuItemI& operator--(MenuItemI& c)
{
    using type = typename std::underlying_type<MenuItemI>::type;
    c = static_cast<MenuItemI>(static_cast<type>(c) - 1);
    if (c == MenuItemI::None)
        c = static_cast<MenuItemI>(static_cast<type>(MenuItemI::Last) - 1);
    return c;
}

// increment++ for menu id
MenuItemI operator++(MenuItemI& c, int)
{
    MenuItemI result = c;
    ++c;
    return result;
}

// decrement-- for menu id
MenuItemI operator--(MenuItemI& c, int)
{
    MenuItemI result = c;
    --c;
    return result;
}

MenuInicioScene::MenuInicioScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // background
    auto background = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::MenuBack), gameManager->getRenderer());

    background->setPosition(30, 20);

    background->setSize(gameManager->getWindowWidth() - 60, static_cast<int>(gameManager->getWindowHeight() / 1.5f) - 20);
    addObject(background);

    startText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "START");
    startText->setColor(colorPressed);
    startText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startText->getWidth() / 2.0f), background->getHeight() + 25);
    addObject(startText);

    creditsText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CREDITS");
    creditsText->setColor(colorStandard);
    creditsText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    creditsText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startText->getWidth() / 2.0f), background->getHeight() + 80);
    addObject(creditsText);

   

    // exit menu
    exitText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), " EXIT");
    exitText->setSize(static_cast<int>(gameManager->getWindowWidth() / 5.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    exitText->setPosition(startText->getPositionX(), creditsText->getPositionY() + exitText->getHeight() + 30);
    addObject(exitText);
    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::MainMenu));
}

void MenuInicioScene::onEnter()
{
    menuMusic->play();
}

void MenuInicioScene::onExit()
{
    menuMusic->stop();
}

void MenuInicioScene::onEvent(const SDL_Event& event)
{
    Scene::onEvent(event);
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.scancode)
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

void MenuInicioScene::onMenuItemSelect()
{
    // reset menu items color
    startText->setColor(colorStandard);
    creditsText->setColor(colorStandard);

    exitText->setColor(colorStandard);
    // change color of selected menu item
    switch (currentSelectedMenu)
    {
    case MenuItemI::Start:
        startText->setColor(colorPressed);
        break;
    case MenuItemI::Credits:
        creditsText->setColor(colorPressed);
        break;
    case MenuItemI::Exit:
        exitText->setColor(colorPressed);
        break;
    default:
        break;
    }
}

void MenuInicioScene::onMenuItemPress()
{
    switch (currentSelectedMenu)
    {
    case MenuItemI::Start:
        // go to level scene
        gameManager->getSceneManager()->addScene("menu", std::make_shared<MenuScene>(gameManager)); 
        gameManager->getSceneManager()->activateScene("menu");
        break;
    case MenuItemI::Credits:
        // go to level scene
        gameManager->getSceneManager()->addScene("credits", std::make_shared<CreditsScene>(gameManager));
        gameManager->getSceneManager()->activateScene("credits");
        break;

    case MenuItemI::Exit:
        // stop gameManager loop
        gameManager->stop();
        break;
    default:
        break;
    }
}
