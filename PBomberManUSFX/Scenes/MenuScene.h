#pragma once

#include <SDL.h>
#include <memory>

#include "../Entities/Music.h"
#include "../Entities/Text.h"
#include "../Scenes/Scene.h"
#include "../Skins.h"
/**
    * @brief Menu id
    *
    */
enum class MenuItem
{
    None,
    StartPlayer1,
    StartPlayer2,
    StartPlayer3,
    StartPlayer4,
    StartPlayer5,
    StartPlayer6,
    Exit,
    Last
};
/**
    * @brief Menu Scene
    *
    */
class MenuScene : public Scene
{
    public:
    /**
        * @brief Construct a new Menu Scene
        *
        * @param game
        */
    MenuScene(GameManager* game);
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

    //std::shared_ptr<Text> startText = nullptr;      // menu start
    //Text* startText = nullptr; Es lo mismo que la linea anterior
    
    std::shared_ptr<Text> startPlayer1Text = nullptr;      // menu start payer1
    std::shared_ptr<Text> startPlayer2Text = nullptr;      // menu start payer1
    std::shared_ptr<Text> startPlayer3Text = nullptr;      // menu start payer1
    std::shared_ptr<Text> startPlayer4Text = nullptr;      // menu start payer1
    std::shared_ptr<Text> startPlayer5Text = nullptr;      // menu start payer1
    std::shared_ptr<Text> startPlayer6Text = nullptr;      // menu start payer1
    std::shared_ptr<Text> exitText = nullptr;       // menu exit
    std::shared_ptr<Music> menuMusic = nullptr;     // menu music
    MenuItem currentSelectedMenu = MenuItem::StartPlayer1; // current selected menu

    // const colors for menu selection
    const SDL_Color colorStandard = {255, 255, 255, 255};
    const SDL_Color colorPressed = { 224, 30, 55, 255};
};

