#pragma once

#include <SDL.h>
#include <memory>
#include <vector>
#include "Animation.h"

/**
    * @brief Sprite object - for drawable objects
    *
*/

class Sprite 
{
protected:
    SDL_Renderer* renderer = nullptr;               // SDL2 renderer
    std::shared_ptr<SDL_Texture> texture = nullptr; // SDL2 texture
    //SDL_Texture* texture = nullptr;               // SDL2 texture
    SDL_Rect rect;                                  // size and position of texture on the screen
    SDL_Rect clip;                                  // what part of texture to draw on the screen
    SDL_RendererFlip flipping = SDL_FLIP_NONE;      // flip of texture

private:
    bool isAttachedToCamera = false; // follow to camera
    std::vector<std::shared_ptr<Animation>> animations; // array of animations

public:
    /**
        * @brief Construct a new Sprite object
        *
        * @param texture - SDL texture
        * @param renderer - SDL Renderer
        */
    Sprite(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer);
    //Sprite(SDL_Texture* texture, SDL_Renderer* renderer);
    /**
        * @brief Add animation to sprite
        *
        * @param animation - animation
        */
   
    void setSize(const int _width, const int _height);
    /**
     * @brief Set the Position of object
     *
     * @param x - position x
     * @param y - position y
     */
    void setPosition(const int _x, const int _y);
    /**
     * @brief Set the Clip of source texture
     *
     * @param width
     * @param height
     * @param x - position x
     * @param y - position y
     */
    void setClip(const int _width, const int _height, const int _x, const int _y);
    /**
     * @brief Attach object to camera movement
     *
     * @param isAttached - attach if true
     */
    void attachToCamera(bool _isAttached = true);
    /**
     * @brief Get the Width of object
     *
     * @return int - width
     */
    int getWidth() const;
    /**
     * @brief Get the Height of object
     *
     * @return int - height
     */
    int getHeight() const;
    /**
     * @brief Get the Position X of object
     *
     * @return int - position X
     */
    int getPositionX() const;
    /**
     * @brief Get the Position Y of object
     *
     * @return int - position Y
     */
    int getPositionY() const;
    /**
     * @brief Get Rect of object
     *
     * @return SDL_Rect& - rect
     */
    const SDL_Rect& getRect() const;
    /**
     * @brief Set the Flip object
     *
     * @param flip - flip of texture
     */
    void setFlip(SDL_RendererFlip flip);
   
    
    void addAnimation(std::shared_ptr<Animation> animation);
    //void addAnimation(Animation* animation);
    /**
        * @brief Node update
        *
        * @param delta - time in ms
        */
    
    /**
     * @brief Update object
     *
     * @param delta - time in milliseconds
     */
    virtual void update(const unsigned int _delta);
    /**
     * @brief Draw object on the screen
     *
     * @param SDL_Rect - camera position
     */
    void render(const SDL_Rect& _camera) const;
};

