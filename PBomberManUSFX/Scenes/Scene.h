#ifndef _BOMBERMAN_SCENES_SCENE_H_
#define _BOMBERMAN_SCENES_SCENE_H_

#include <SDL.h>
#include <vector>

#include "../Entities/GameGraphicObject.h"

class GameManager;
/**
    * @brief Scene base class
    *
    */
class Scene
{
    public:
    /**
        * @brief Construct a new Scene object
        *
        * @param game - pointer to game
        */
    Scene(GameManager* _gameManager);
    /**
        * @brief Destroy the Scene object
        *
        */
    virtual ~Scene();
    /**
        * @brief Add object to scene for drawing
        *
        * @param object
        */
    void addObject(std::shared_ptr<GameObject> object);
    /**
        * @brief Add object to scene for drawing to specific position
        *
        * @param object
        * @param position - position where to insert object
        */
    void insertObject(std::shared_ptr<GameObject> object, int position);
    /**
        * @brief Remove object from scene
        *
        * @param object
        */
    void removeObject(std::shared_ptr<GameObject> object);
    /**
        * @brief Set the Camera object to specific position
        *
        * @param x - position x
        * @param y - position y
        */
    void setCamera(const int x, const int y);
    /**
        * @brief Called when scene become activated
        *
        */
    virtual void onEnter();
    /**
        * @brief CAlled when scene become deactivated
        *
        */
    virtual void onExit();
    /**
        * @brief Trigger on SDL2 event if scene is active
        *
        * @param event - SDL2 event
        */
    virtual void onEvent(const SDL_Event& event);
    /**
        * @brief Trigger on update if scene is active
        *
        * @param delta - time in milliseconds
        */
    virtual void update(const unsigned int delta);
    /**
        * @brief Draw objects on the screen
        *
        */
    void render() const;

    protected:
    GameManager* gameManager = nullptr; // pointer to game for use in all scenes

    private:
    std::vector<std::shared_ptr<GameObject>> objects; // objects to update and render
    std::vector<GameObject*> vectorObjectosJuego;
    
    SDL_Rect camera;                              // camera position
};

#endif // _BOMBERMAN_SCENES_SCENE_H_
