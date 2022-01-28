#pragma once

#include <SDL.h>
#include <memory>

#include "../Entities/Music.h"
#include "../Entities/Text.h"
#include "../Scenes/Scene.h"
#include "../Scenes/MenuInicioScene.h"

/**
    * @brief Menu id
    *
    */
enum class MenuItemC
{
    None,
    Back,
    Last
};
/**
    * @brief Menu Scene
    *
    */
class CreditsScene : public Scene
{
public:
    /**
        * @brief Construct a new Menu Scene
        *
        * @param game
        */
    CreditsScene(GameManager* game);
    /**
        * @brief Called when scene was activated
        *
        */
    virtual void onEnter() override;
    /**
        * @brief Called when scene was deactivated
        *
        */
    virtual void onExit() override;
    /**
        * @brief Trigger on SDL2 event if scene is active
        *
        * @param event - SDL2 event
        */
    virtual void onEvent(const SDL_Event& event) override;

private:
    /**
        * @brief called when menu item was selected
        *
        */
    void onMenuItemSelect();
    /**
        * @brief called when menu item was pressed
        *
        */
    void onMenuItemPress();


    std::shared_ptr<Text> backText = nullptr;      // menu start back

    MenuItemC currentSelectedMenu = MenuItemC::Back; // current selected menu

    std::shared_ptr<Music> menuMusic = nullptr;     // menu music

    // const colors for menu selection
    const SDL_Color colorStandard = { 255, 255, 255, 255 };
    const SDL_Color colorPressed = { 224, 30, 55, 255 };
};