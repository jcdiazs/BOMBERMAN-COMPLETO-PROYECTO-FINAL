#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>

#include "GameManager.h"
#include "./Scenes/LevelScene.h"
#include "./Scenes/MenuScene.h"
#include "./Scenes/MenuInicioScene.h"
#include "./Scenes/YouWinScene.h"


GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance(std::string _windowsName, int _width, int _height) {

    if (instance == 0) {
        instance = new GameManager(_windowsName, _width, _height);
    }

    return instance;
}

GameManager::GameManager(const std::string _windowName, const int width, const int height)
    : windowWidth(width), windowHeight(height), windowName(_windowName)
{
    keyboardInput = KeyboardInput::Instance();
    //std::cout << keyboardInput << std::endl;
}

GameManager::~GameManager()
{
    delete sceneManager;
    delete assetManager;
    // delete SDL2 C pointers
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // SDL2 finish
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool GameManager::init() {
    //Initialization flag
    bool success = true;

    // let's init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    // let's init SDL2 TTF
    if (TTF_Init() != 0)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    // let's init SDL2 Image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        success = false;
    }

    // let's init SDL2 Mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        success = false;
    }

    // create a window
    window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    // create a renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    // we need new size due to possible high resolution on mac and ios
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    windowWidth = w;
    windowHeight = h;

    assetManager = new AssetManager();
    sceneManager = new SceneManager();

    return success;
}

void GameManager::execute()
{
    if(isRunning)
    {
        return;
    }

    isRunning = true;

    if (!init()) {
        cout << "Failed to initialize!" << endl;
        return;
    }

    // load assets
    assetManager->load(renderer);
    //create menu inicio //se activa desde ahi cuando es la escena que inicia
    sceneManager->addScene("inicio", std::make_shared<MenuInicioScene>(this));
    sceneManager->activateScene("inicio");
    // create menu scene
    //sceneManager->addScene("menu", std::make_shared<MenuScene>(this));
    //sceneManager->activateScene("menu");
    sceneManager->addScene("you win", std::make_shared<YouWinScene>(this));
    SDL_Event event;

    while(isRunning)
    {
        // check SDL2 events
        while(SDL_PollEvent(&event))
        {
            // send event to current scene
            sceneManager->onEvent(event);
            // stop loop on quit
            if(event.type == SDL_QUIT)
            {
                stop();
            }
        }

        // calculate delta
        Uint32 tickTime = SDL_GetTicks();
        Uint32 delta = tickTime - lastTickTime;
        lastTickTime = tickTime;
        // update current scene
        sceneManager->update(delta);

        // clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        // render current scene
        sceneManager->render();
        // flip the backbuffer
        SDL_RenderPresent(renderer);
    }
}

void GameManager::stop()
{
    isRunning = false;
}

int GameManager::getWindowWidth() const
{
    return windowWidth;
}

int GameManager::getWindowHeight() const
{
    return windowHeight;
}

SDL_Renderer* GameManager::getRenderer() const
{
    return renderer;
}

SceneManager* GameManager::getSceneManager() const
{
    return sceneManager;
}

AssetManager* GameManager::getAssetManager() const
{
    return assetManager;
}
