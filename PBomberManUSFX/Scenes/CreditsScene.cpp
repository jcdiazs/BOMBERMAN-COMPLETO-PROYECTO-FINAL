#include <string>

#include "../Entities/Sprite.h"
#include "../GameManager.h"
#include "../Scenes/CreditsScene.h"


// ++increment for menu id
MenuItemC& operator++(MenuItemC& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItemC>(static_cast<type>(c) + 1);
    if (c == MenuItemC::Last)
        c = static_cast<MenuItemC>(static_cast<type>(MenuItemC::None) + 1);
    return c;
}

// --decrement for menu id
MenuItemC& operator--(MenuItemC& c)
{
    using type = typename std::underlying_type<MenuItemC>::type;
    c = static_cast<MenuItemC>(static_cast<type>(c) - 1);
    if (c == MenuItemC::None)
        c = static_cast<MenuItemC>(static_cast<type>(MenuItemC::Last) - 1);
    return c;
}

// increment++ for menu id
MenuItemC operator++(MenuItemC& c, int)
{
    MenuItemC result = c;
    ++c;
    return result;
}

// decrement-- for menu id
MenuItemC operator--(MenuItemC& c, int)
{
    MenuItemC result = c;
    --c;
    return result;
}

CreditsScene::CreditsScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // background
    auto background = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::Credits), gameManager->getRenderer());

    background->setPosition(0, 0);

    background->setSize(gameManager->getWindowWidth(), gameManager->getWindowHeight());
    addObject(background);

    backText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "BACK");
    backText->setColor(colorPressed);
    backText->setSize(102, 29);
    backText->setPosition(340, 540);
    addObject(backText);

 
    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::Credits));
}

void CreditsScene::onEnter()
{
    menuMusic->play();
}

void CreditsScene::onExit()
{
    menuMusic->stop();
}

void CreditsScene::onEvent(const SDL_Event& event)
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

void CreditsScene::onMenuItemSelect()
{
    // reset menu items color
    backText->setColor(colorStandard);

    // change color of selected menu item
    switch (currentSelectedMenu)
    {
    case MenuItemC::Back:
        backText->setColor(colorPressed);
        break;

    default:
        break;
    }
}

void CreditsScene::onMenuItemPress()
{
    switch (currentSelectedMenu)
    {
    case MenuItemC::Back:
        // go to level scene

        gameManager->getSceneManager()->activateScene("inicio");
        break;

    default:
        break;
    }
}
