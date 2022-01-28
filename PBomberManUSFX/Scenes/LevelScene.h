#ifndef _BOMBERMAN_LEVEL_SCENE_H_
#define _BOMBERMAN_LEVEL_SCENE_H_

#include <SDL.h>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "../Const.h"
#include "../Entities/Enemy.h"
#include "../Entities/Item.h"
#include "../Entities/Music.h"
#include "../Entities/Player.h"
#include "../Entities/Sound.h"
#include "../Entities/Text.h"
#include "../Scenes/Scene.h"
#include "../Factories/Factory.h"
#include "../Factories/FactoryGameClasico.h"
#include "../Factories/FactoryGameCartoon.h"
#include "../Entities/ClasicoPlayer.h"
#include "../Skins.h"
#include "../GameTextures.h"

#include "../Adapters/WallPacman.h"
#include "../Adapters/TileGraph.h"
#include "../Adapters/Tile.h"

#include "../Decorator/DecoratorWall.h"
#include "../Decorator/BorderDecoratorWall.h"
#include "../Decorator/ShineDecoratorWall.h"

/**
    * @brief Level Scene
    *
    */
class LevelScene : public Scene
{
public:
    Factory* factory;

    /**
        * @brief Construct a new Level Scene
        *
        * @param game - game pointer
        * @param stage - stage number
        */
    LevelScene(GameManager* game, const unsigned int _stage, const unsigned int _prevScore);
    LevelScene(GameManager* game, Skin _skin, const unsigned int _stage, const unsigned int _prevScore);
    
    /**
        * @brief Catch SDL2 events
        *
        * @param event - SDL2 event
        */
    virtual void onEvent(const SDL_Event& event) override;
    /**
        * @brief Update level scene
        *
        * @param delta - delta time since previous update in milliseconds
        */
    virtual void update(const unsigned int delta) override;
    // timers in ms const
    const int levelTimerStart = 200500;
    int levelTimer = levelTimerStart;

    //min max enemies
    int minEnemiesOnLevel = 1;    // minimum enemies count on level
    int maxEnemiesOnLevel = 1;   // maximum enemies count on level
    //vida
    int vida = 3;

private:
    
    // spawn and generation of map objects
    void spawnTextObjects();
    void generateTileMap();

    void generateEnemies();
    void generateItems();
    void spawnMetal(const int positionX, const int positionY);
    void spawnGrass(const int positionX, const int positionY);
    void spawnBrick(const int positionX, const int positionY);
    void spawnStone(const int positionX, const int positionY);
    void spawnWallPacman(const int positionX, const int positionY, Tile* _tile);

    void spawnPlayer(const int positionX, const int positionY);
    void spawnEnemy(GameTexture texture, AIType type, const int positionX, const int positionY);
    void spawnItem(GameTexture texture, const int positionX, const int positionY);
    void spawnBomb(GameGraphicObject* object);
    void spawnBang(GameGraphicObject* object);

    void spawnDoor(GameGraphicObject* object);

     void spawnDoorItemTP(GameGraphicObject* object);
    void spawnDoorItemV(GameGraphicObject* object);
    void spawnDoorItemAV(GameGraphicObject* object);
    void spawnDoorItemT(GameGraphicObject* object);
    void spawnDoorItemAT(GameGraphicObject* object);
    void spawnDoorItemTort(GameGraphicObject* object);
    void spawnDoorItemVD(GameGraphicObject* object);

    /**
        * @brief Finish level
        *
        */
    void finish() const;
    /**
        * @brief GameManager over
        *
        */
    void gameOver();

    /**
        * @brief Exit level
        *
        */
    void exit() const;

    // timers update
    void updateTimers(const unsigned int delta);
    void updateLevelTimer();
    void updateBombTimer(const unsigned int delta);
    void updateBangTimer(const unsigned int delta);
    void updateGameOverTimer(const unsigned int delta);
    // update movement
    void updateMovement(const bool isPressed, const int keycode);
    // update camera
    void updateCamera();
    // score update
    void updateScore();
    // vida update
    void updateVida();
    // update collisions
    void updatePlayerCollision();
    void updateEnemiesCollision();
    void updateItemsCollision();
    void updateBangsCollision();
    bool isCollisionDetected(const SDL_Rect& rect1, const SDL_Rect& rect2) const;
    // destroy brick
    void destroyBrick(std::shared_ptr<GameGraphicObject> brick);

    void destroyBrickTP(std::shared_ptr<GameGraphicObject> brick);
    void destroyBrickV(std::shared_ptr<GameGraphicObject> brick);
    void destroyBrickAV(std::shared_ptr<GameGraphicObject> brick);
    void destroyBrickT(std::shared_ptr<GameGraphicObject> brick);
    void destroyBrickAT(std::shared_ptr<GameGraphicObject> brick);
    void destroyBrickTort(std::shared_ptr<GameGraphicObject> brick);
    void destroyBrickVD(std::shared_ptr<GameGraphicObject> brick);

    // enemy follow to player if in attack radius
    void followToPlayer(Enemy* enemy);

    bool crearObjetosJuego(string _path);

    // timers in ms const
    //const int levelTimerStart = 200500;
    const int levelTimerUpdateText = 1000;
    const int bombTimerStart = 1500;
    const int bangTimerStart = 800;
    const int gameOverTimerStart = 1000;
    const int winTimerStart = 200;
    // const for score
    const unsigned int scoreRewardForKill = 100;
    const unsigned int scoreRewardForStage = 200;

    std::shared_ptr<Music> menuMusic = nullptr;                       // menu music
    std::shared_ptr<Sound> gameoverSound = nullptr;                   // game over sound
    std::shared_ptr<Sound> winSound = nullptr;                        // win sound
    std::shared_ptr<Sound> explosionSound = nullptr;                  // explosion sound
    
    std::shared_ptr<Sound> itemTeleportSound = nullptr;
    std::shared_ptr<Sound> itemVidaSound = nullptr;
    std::shared_ptr<Sound> itemAntiVidaSound = nullptr;
    std::shared_ptr<Sound> itemTortugaSound = nullptr;
    std::shared_ptr<Sound> itemAntiTiempoSound = nullptr;
    std::shared_ptr<Sound> itemVelocidadSound = nullptr;
    std::shared_ptr<Sound> itemTiempoSound = nullptr;
    
    std::shared_ptr<Text> timerNumber = nullptr;                      // timer
    std::shared_ptr<Text> scoreNumber = nullptr;                      // score
    std::shared_ptr<Text> vidasNumber = nullptr;
    std::shared_ptr<Player> player = nullptr;                         // player
    std::shared_ptr<Sprite> bomb = nullptr;                           // player's bomb

    std::shared_ptr<Sprite> door = nullptr;                           // door for level finish

    std::shared_ptr<Sprite> doorItemTP = nullptr;
    std::shared_ptr<Sprite> doorItemV = nullptr;                           // door for level finish
    std::shared_ptr<Sprite> doorItemAV = nullptr;                           // door for level finish
    std::shared_ptr<Sprite> doorItemT = nullptr;                           // door for level finish
    std::shared_ptr<Sprite> doorItemAT = nullptr;                           // door for level finish
    std::shared_ptr<Sprite> doorItemTort = nullptr;                           // door for level finish
    std::shared_ptr<Sprite> doorItemVD = nullptr;

    std::shared_ptr<Sprite> item = nullptr;
    std::vector<std::shared_ptr<Enemy>> enemies;                      // enemies
    std::vector<std::shared_ptr<Item>> items;
    std::vector<std::pair<GameTile, std::shared_ptr<GameGraphicObject>>> collisions; // collisions
    std::vector<std::shared_ptr<GameGraphicObject>> bangs;                       // bomb's bang
    GameTile tiles[tileArrayHeight][tileArrayWidth];                      // tilemap


    int playerDirectionX = 0; // direction used for control
    int playerDirectionY = 0; // direction used for control
    // timer variables
    //int levelTimer = levelTimerStart;
    int levelTimerDelta = 0;
    int bombTimer = 0;
    int bangTimer = 0;
    int gameOverTimer = 0;
    // bool flags
    bool isGameOver = false;
    bool isPaused = false;
    bool isWin = false;
    // variables
    unsigned int skins = SKIN_JOSH;
    unsigned int score = 0;
    unsigned int stage = 0;

    // level positioning
    int fieldPositionX = 0;
    int fieldPositionY = 0;
    // size of tiles
    int scaledTileSize = 0;
    // last object that used as background (grass)
    int backgroundObjectLastNumber = 0;

    TileGraph* tileGraph;
};

#endif // _BOMBERMAN_LEVEL_SCENE_H_
