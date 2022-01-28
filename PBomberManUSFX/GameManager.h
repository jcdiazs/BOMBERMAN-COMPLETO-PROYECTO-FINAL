#ifndef _BOMBERMAN_GAME_H_
#define _BOMBERMAN_GAME_H_

#include <SDL.h>
#include <memory>
#include <iostream>
#include <string>

#include "./Managers/AssetManager.h"
#include "./Managers/SceneManager.h"
#include "./system/KeyboardInput.h"


class GameManager
{
 private:
    // SDL2 C pointers
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    SceneManager* sceneManager = nullptr; // scene manager
    AssetManager* assetManager = nullptr; // asset manager

    // screen parameters
    std::string windowName;
    int windowWidth = 0;
    int windowHeight = 0;

    bool isRunning = false;  // game loop status
    Uint32 lastTickTime = 0; // last time for delta calculation
    GameManager(const std::string windowName, const int windowWidth, const int windowHeight);

public:
    static GameManager* instance;
    KeyboardInput* keyboardInput;

    static GameManager* getInstance(std::string _windowsName, int _width, int _height);
    /**
        * @brief Create GameManager
        *
        * @param windowName - name of window
        * @param windowWidth - width of window
        * @param windowHeight - height of window
        */
    
    /**
        * @brief Destroy GameManager
        *
        */
    ~GameManager();
    /**
        * @brief Run game loop
        *
        */
    bool init();
    void execute();
    /**
        * @brief Stop game loop
        *
        */
    void stop();
    /**
        * @brief Get the Window Width
        *
        * @return int - window width
        */
    int getWindowWidth() const;
    /**
        * @brief Get the Window Height
        *
        * @return int - window height
        */
    int getWindowHeight() const;
    /**
        * @brief Get SDL2 Renderer
        *
        * @return SDL_Renderer* - SDL2 renderer
        */
    SDL_Renderer* getRenderer() const;
    /**
        * @brief Get Scene Manager reference
        *
        * @return SceneManager* - scene manager reference
        */
    SceneManager* getSceneManager() const;
    /**
        * @brief Get Asset Manager reference
        *
        * @return AssetManager* - asset manager reference
        */
    AssetManager* getAssetManager() const;
};

#endif // _BOMBERMAN_GAME_H_
