#pragma once

#include <SDL.h>
#include <memory>
#include "GameObject.h"

/**
    * @brief Base class for GameGraphicObjects
    *
    */
class GameGraphicObject: public GameObject
{
    public:
    /**
        * @brief Construct a new GameGraphicObject
        *
        * @param renderer - SDL2 renderer
        */
    GameGraphicObject(SDL_Renderer* renderer);
    /**
        * @brief Destroy the GameGraphicObject
        *
        */
    virtual ~GameGraphicObject();
    /**
        * @brief Set the Size of GameGraphicObject
        *
        * @param width
        * @param height
        */
    void setSize(const int width, const int height);
    /**
        * @brief Set the Position of GameGraphicObject
        *
        * @param x - position x
        * @param y - position y
        */
    void setPosition(const int x, const int y);
    /**
        * @brief Set the Clip of source texture
        *
        * @param width
        * @param height
        * @param x - position x
        * @param y - position y
        */
    void setClip(const int width, const int height, const int x, const int y);
    /**
        * @brief Attach GameGraphicObject to camera movement
        *
        * @param isAttached - attach if true
        */
    void attachToCamera(bool isAttached = true);
    /**
        * @brief Get the Width of GameGraphicObject
        *
        * @return int - width
        */
    int getWidth() const;
    /**
        * @brief Get the Height of GameGraphicObject
        *
        * @return int - height
        */
    int getHeight() const;
    /**
        * @brief Get the Position X of GameGraphicObject
        *
        * @return int - position X
        */
    int getPositionX() const;
    /**
        * @brief Get the Position Y of GameGraphicObject
        *
        * @return int - position Y
        */
    int getPositionY() const;
    /**
        * @brief Get Rect of GameGraphicObject
        *
        * @return SDL_Rect& - rect
        */
    const SDL_Rect& getRect() const;
    /**
        * @brief Set the Flip GameGraphicObject
        *
        * @param flip - flip of texture
        */
    void setFlip(SDL_RendererFlip flip);
    /**
        * @brief Update GameGraphicObject
        *
        * @param delta - time in milliseconds
        */
    virtual void update(const unsigned int delta);
    /**
        * @brief Draw GameGraphicObject on the screen
        *
        * @param SDL_Rect - camera position
        */
    void render(const SDL_Rect& camera);
    virtual void handleEvent(SDL_Event* _event) {};
    protected:
    SDL_Renderer* renderer = nullptr;               // SDL2 renderer
    std::shared_ptr<SDL_Texture> texture = nullptr; // SDL2 texture
    SDL_Rect rect;                                  // size and position of texture on the screen
    SDL_Rect clip;                                  // what part of texture to render on the screen
    SDL_RendererFlip flipping = SDL_FLIP_NONE;      // flip of texture

    private:
    bool isAttachedToCamera = true; // follow to camera
};