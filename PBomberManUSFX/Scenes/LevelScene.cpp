#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <string>

#include "../Entities/Sprite.h"
#include "../Entities/WallBrick.h"
#include "../Entities/WallMetal.h"
#include "../Entities/WallStone.h"
#include "../Entities/SoilGrass.h"
#include "../Adapters/WallPacmanAdapter.h"
#include "../Adapters/GameObjectPacman.h"
#include "../Adapters/WallPacman.h"
#include "../Adapters/Tile.h"
#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/LevelScene.h"
#include "../Scenes/StageScene.h"
#include "../Util/Pathfinding.h"

LevelScene::LevelScene(GameManager* _gameManager, const unsigned int _stage, const unsigned int prevScore)
    : Scene(_gameManager), score(prevScore), stage(_stage)
{
    
    // common field parameters
    fieldPositionX = 0;
    fieldPositionY = gameManager->getWindowHeight() / 15;
    //fieldPositionY = 0;
    const float scale = (gameManager->getWindowHeight() - fieldPositionY) / static_cast<float>(tileArrayHeight * tileSize);
    scaledTileSize = static_cast<int>(round(scale * tileSize));
    
    Tile::tileHeight = scaledTileSize;
    Tile::tileWidth = scaledTileSize;

    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::Level));
    menuMusic->play();
    // sounds
    gameoverSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Lose));
    winSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Win));
    explosionSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Explosion));
    // render text
    spawnTextObjects();
    // generate tile map
    //generateTileMap();
    // 
    
    //tileGraph = new TileGraph(25, 15);
    crearObjetosJuego("resources/level1.txt");
    // prepare player
    spawnPlayer(fieldPositionX + playerStartX * scaledTileSize, fieldPositionY + playerStartY * scaledTileSize);
    // generate enemies
    generateEnemies();
    // generate enemies
    generateItems();
    // set timer
    updateLevelTimer();
}

LevelScene::LevelScene(GameManager* _gameManager, Skin _skin, const unsigned int _stage, const unsigned int prevScore)
    : Scene(_gameManager), skins(_skin), score(prevScore), stage(_stage)
{
    
    /*if (gameVersion == GameVersion::GAMEVERSION_CARTOON) {
        factory = new FactoryGameCartoon();
    }
    else if (gameVersion == GameVersion::GAMEVERSION_CLASIC) {
        factory = new FactoryGameClasico();
    }*/
    /*else if (gameVersion == GameVersion::GAMEVERSION_CUSTOM) {
        factory = new FactoryGamePersonalizado();
    }*/
    /*else {
        factory = new FactoryGameRealista();
    }*/

    // common field parameters
    fieldPositionX = 0;
    //fieldPositionY = 0;
    fieldPositionY = gameManager->getWindowHeight() / 15;
    const float scale = (gameManager->getWindowHeight() - fieldPositionY) / static_cast<float>(tileArrayHeight * tileSize);
    scaledTileSize = static_cast<int>(round(scale * tileSize));
    Tile::tileHeight = scaledTileSize;
    Tile::tileWidth = scaledTileSize;

    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::Level));
    menuMusic->play();
    // sounds
    gameoverSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Lose));
    winSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Win));
    explosionSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Explosion));

    itemTeleportSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Teleport));
    itemVidaSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Vida));
    itemAntiVidaSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::AntiVida));
    //itemRayoSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Rayo));
    itemTortugaSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Tortuga));
    itemAntiTiempoSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::AntiTiempo));
    itemVelocidadSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Velocidad));
    itemTiempoSound = std::make_shared<Sound>(gameManager->getAssetManager()->getSound(SoundEnum::Tiempo));

    // render text
    spawnTextObjects();
    // generate tile map
    //generateTileMap();
    // 
    //tileGraph = new TileGraph(25, 15);
    crearObjetosJuego("resources/level1.txt");
    // prepare player
    spawnPlayer(fieldPositionX + playerStartX * scaledTileSize,
        fieldPositionY + playerStartY * scaledTileSize);
    // generate enemies
    generateEnemies();

    generateItems();
    // set timer
    updateLevelTimer();
}

void LevelScene::spawnTextObjects()
{
    const int fontWidth = static_cast<int>(gameManager->getWindowWidth() / 32.0f);
    const int fontHeight = static_cast<int>(gameManager->getWindowHeight() / 30.0f);
    // timer text
    auto timerText =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "s");
    timerText->setSize(20,20);
    timerText->setPosition(105, 10);
    timerText->attachToCamera(false);
    addObject(timerText);
    backgroundObjectLastNumber++;

    // timer number
    timerNumber = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "000");
    timerNumber->setSize(fontWidth * 3, fontHeight);
    timerNumber->setPosition(20,10);
    timerNumber->attachToCamera(false);
    addObject(timerNumber);
    backgroundObjectLastNumber++;

    // scoretxt
    std::string scoreText = std::to_string(score);
    scoreNumber =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), scoreText);
    scoreNumber->setSize(fontWidth * static_cast<int>(scoreText.size()), fontHeight);
    scoreNumber->setPosition(480, 10);
    scoreNumber->attachToCamera(false);
    addObject(scoreNumber);
    backgroundObjectLastNumber++;
    // score
    std::string scoreT = "Score";
    auto scoretxt =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), scoreT);
    scoretxt->setSize(fontWidth * static_cast<int>(scoreT.size()), fontHeight);
    scoretxt->setPosition(310, 10);
    scoretxt->attachToCamera(false);
    addObject(scoretxt);
    backgroundObjectLastNumber++;

    // vida text
    std::string vTextConv = "f";
    auto vText =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont2(), gameManager->getRenderer(), vTextConv);
    vText->setSize(22, 20);
    vText->setColor({ 224, 30, 55, 255 });
    vText->setPosition(220, 12);
    vText->attachToCamera(false);
    addObject(vText);
    backgroundObjectLastNumber++;

    //vidas
    std::string vidasText = std::to_string(vida);
    vidasNumber =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), vidasText);
    vidasNumber->setSize(fontWidth * static_cast<int>(vidasText.size()), fontHeight);
    vidasNumber->setPosition(180, 10);
    vidasNumber->attachToCamera(false);
    addObject(vidasNumber);
    backgroundObjectLastNumber++;

    // stage
    std::string stageTextConv = "Nivel " + std::to_string(stage);
    auto stageText =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), stageTextConv);
    stageText->setSize(fontWidth * static_cast<int>(stageTextConv.size()), fontHeight);
    stageText->setPosition(gameManager->getWindowWidth() - 30 - stageText->getWidth(),
                            timerText->getPositionY());
    stageText->setColor({ 30, 145, 214, 255 });
    stageText->attachToCamera(false);
    addObject(stageText);
    backgroundObjectLastNumber++;
}

void LevelScene::generateTileMap()
{
    // we need random bricks
    //const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    //auto randBrick = std::bind(std::uniform_int_distribution<int>(0, brickSpawnRandomize),
    //                            std::mt19937(static_cast<unsigned int>(seed)));

    //// iterate every tile
    //for(int i = 0; i < static_cast<int>(tileArrayHeight); i++)
    //{
    //    for(int j = 0; j < static_cast<int>(tileArrayWidth); j++)
    //    {
    //        tiles[i][j] = baseTiles[i][j];
    //        // generate random bricks
    //        if(tiles[i][j] == GameTile::Grass)
    //        {
    //            if(randBrick() == 0)
    //            {
    //                tiles[i][j] = GameTile::Brick;
    //            }
    //        }
    //        // spawn brick and grass
    //        if(tiles[i][j] == GameTile::Brick)
    //        {
    //            spawnGrass(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
    //            spawnBrick(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
    //        }
    //        // spawn grass
    //        if(tiles[i][j] == GameTile::Grass || tiles[i][j] == GameTile::EmptyGrass)
    //        {
    //            spawnGrass(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
    //        }
    //        // spawn stone
    //        if(tiles[i][j] == GameTile::Stone)
    //        {
    //            spawnStone(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
    //            //spawnWallPacman(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
    //            //spawnMetal(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
    //        }
    //    }
    //}
}

void LevelScene::spawnGrass(const int positionX, const int positionY)
{
    if (stage == 1) {
        auto grass = std::make_shared<SoilGrass>(gameManager->getAssetManager()->getTexture(GameTexture::Grass),
            gameManager->getRenderer());
        grass->setPosition(positionX, positionY);
        grass->setSize(scaledTileSize, scaledTileSize);
        addObject(grass);
        backgroundObjectLastNumber++;
    }
    else if (stage == 2)
    {
        auto grass = std::make_shared<SoilGrass>(gameManager->getAssetManager()->getTexture(GameTexture::RealGrass),
            gameManager->getRenderer());
        grass->setPosition(positionX, positionY);
        grass->setSize(scaledTileSize, scaledTileSize);
        addObject(grass);
        backgroundObjectLastNumber++;
    }
    else if (stage == 3)
    {
        auto grass = std::make_shared<SoilGrass>(gameManager->getAssetManager()->getTexture(GameTexture::CustomGrass),
            gameManager->getRenderer());
        grass->setPosition(positionX, positionY);
        grass->setSize(scaledTileSize, scaledTileSize);
        addObject(grass);
        backgroundObjectLastNumber++;
    }
    else if (stage == 4) 
    {
        auto grass = std::make_shared<SoilGrass>(gameManager->getAssetManager()->getTexture(GameTexture::CartoonGrass),
            gameManager->getRenderer());
        grass->setPosition(positionX, positionY);
        grass->setSize(scaledTileSize, scaledTileSize);
        addObject(grass);
        backgroundObjectLastNumber++;
    }
    else 
    {
        auto grass = std::make_shared<SoilGrass>(gameManager->getAssetManager()->getTexture(GameTexture::CustomGrass),
            gameManager->getRenderer());
        grass->setPosition(positionX, positionY);
        grass->setSize(scaledTileSize, scaledTileSize);
        addObject(grass);
        backgroundObjectLastNumber++;
    }
       
}

void LevelScene::spawnMetal(const int positionX, const int positionY)
{
    auto metal = std::make_shared<WallMetal>(gameManager->getAssetManager()->getTexture(GameTexture::Metal),
        gameManager->getRenderer());
    metal->setPosition(positionX, positionY);
    metal->setSize(scaledTileSize, scaledTileSize);
    addObject(metal);
    backgroundObjectLastNumber++;
}

void LevelScene::spawnBrick(const int positionX, const int positionY)
{
    
    if (stage == 1) {
        auto brick = std::make_shared<WallBrick>(gameManager->getAssetManager()->getTexture(GameTexture::Brick), gameManager->getRenderer());
        brick->setPosition(positionX, positionY);
        brick->setSize(scaledTileSize, scaledTileSize);
        addObject(brick);
        collisions.push_back(std::make_pair(GameTile::Brick, brick));
    }
    else if (stage == 2)
    {
        auto brick = std::make_shared<WallBrick>(gameManager->getAssetManager()->getTexture(GameTexture::RealBrick), gameManager->getRenderer());
        brick->setPosition(positionX, positionY);
        brick->setSize(scaledTileSize, scaledTileSize);
        addObject(brick);
        collisions.push_back(std::make_pair(GameTile::Brick, brick));
    }
    else if (stage == 3)
    {
        auto brick = std::make_shared<WallBrick>(gameManager->getAssetManager()->getTexture(GameTexture::CustomBrick), gameManager->getRenderer());
        brick->setPosition(positionX, positionY);
        brick->setSize(scaledTileSize, scaledTileSize);
        addObject(brick);
        collisions.push_back(std::make_pair(GameTile::Brick, brick));
    }
    else if (stage == 4) 
    {
        auto brick = std::make_shared<WallBrick>(gameManager->getAssetManager()->getTexture(GameTexture::CartoonBrick), gameManager->getRenderer());
        brick->setPosition(positionX, positionY);
        brick->setSize(scaledTileSize, scaledTileSize);
        addObject(brick);
        collisions.push_back(std::make_pair(GameTile::Brick, brick));
    }
    else 
    {
        auto brick = std::make_shared<WallBrick>(gameManager->getAssetManager()->getTexture(GameTexture::CustomBrick), gameManager->getRenderer());
        brick->setPosition(positionX, positionY);
        brick->setSize(scaledTileSize, scaledTileSize);
        addObject(brick);
        collisions.push_back(std::make_pair(GameTile::Brick, brick));
    }
    
}

void LevelScene::spawnStone(const int positionX, const int positionY)
{

    if (stage == 1) {
        auto stone = std::make_shared<WallStone>(gameManager->getAssetManager()->getTexture(GameTexture::Stone), gameManager->getRenderer());
        stone->setPosition(positionX, positionY);
        stone->setSize(scaledTileSize, scaledTileSize);
        std::shared_ptr<GameActor> temp(stone);
        addObject(temp);
        collisions.push_back(std::make_pair(GameTile::Stone, temp));
        backgroundObjectLastNumber++;
    }
    else if (stage == 2)
    {
        auto stone = std::make_shared<WallStone>(gameManager->getAssetManager()->getTexture(GameTexture::RealStone), gameManager->getRenderer());
        stone->setPosition(positionX, positionY);
        stone->setSize(scaledTileSize, scaledTileSize);
        std::shared_ptr<GameActor> temp(stone);
        addObject(temp);
        collisions.push_back(std::make_pair(GameTile::Stone, temp));
        backgroundObjectLastNumber++;
    }
    else if (stage == 3)
    {
        auto stone = std::make_shared<WallStone>(gameManager->getAssetManager()->getTexture(GameTexture::CustomStone), gameManager->getRenderer());
        stone->setPosition(positionX, positionY);
        stone->setSize(scaledTileSize, scaledTileSize);
        std::shared_ptr<GameActor> temp(stone);
        addObject(temp);
        collisions.push_back(std::make_pair(GameTile::Stone, temp));
        backgroundObjectLastNumber++;
    }
    else if (stage == 4)
    {
        auto stone = std::make_shared<WallStone>(gameManager->getAssetManager()->getTexture(GameTexture::CartoonStone), gameManager->getRenderer());
        stone->setPosition(positionX, positionY);
        stone->setSize(scaledTileSize, scaledTileSize);
        std::shared_ptr<GameActor> temp(stone);
        addObject(temp);
        collisions.push_back(std::make_pair(GameTile::Stone, temp));
        backgroundObjectLastNumber++;
    }
    else {
        auto stone = std::make_shared<WallStone>(gameManager->getAssetManager()->getTexture(GameTexture::CustomStone), gameManager->getRenderer());
        stone->setPosition(positionX, positionY);
        stone->setSize(scaledTileSize, scaledTileSize);
        std::shared_ptr<GameActor> temp(stone);
        addObject(temp);
        collisions.push_back(std::make_pair(GameTile::Stone, temp));
        backgroundObjectLastNumber++;
    }
    
 }


void LevelScene::spawnPlayer(const int positionX, const int positionY)
{
    // spawn player

    if (skins == Skin::SKIN_JOSH)
    {
        player = std::make_unique<Player>(gameManager->getAssetManager()->getTexture(GameTexture::Player1), gameManager->getRenderer());
        player->setPosition(positionX, positionY);
        player->setSize(scaledTileSize, scaledTileSize);
        player->setClip(tileSize, tileSize, tileSize * 4, 0);
        addObject(player);
        //player-> speed = 0.01f;
    }
    else if (skins == Skin::SKIN_CLASSIC)
    {
        player = std::make_unique<Player>(gameManager->getAssetManager()->getTexture(GameTexture::Player2), gameManager->getRenderer());
        player->setPosition(positionX, positionY);
        player->setSize(scaledTileSize, scaledTileSize);
        player->setClip(tileSize, tileSize, tileSize * 4, 0);
        addObject(player);
        //player-> speed = 0.01f;
    }
    else if (skins == Skin::SKIN_TYLER)
    {
        player = std::make_unique<Player>(gameManager->getAssetManager()->getTexture(GameTexture::Player3), gameManager->getRenderer());
        player->setPosition(positionX, positionY);
        player->setSize(scaledTileSize, scaledTileSize);
        player->setClip(tileSize, tileSize, tileSize * 4, 0);
        addObject(player);
        //player-> speed = 0.01f;
    }
    else if (skins == Skin::SKIN_BRUNO)
    {
        player = std::make_unique<Player>(gameManager->getAssetManager()->getTexture(GameTexture::Player4), gameManager->getRenderer());
        player->setPosition(positionX, positionY);
        player->setSize(scaledTileSize, scaledTileSize);
        player->setClip(tileSize, tileSize, tileSize * 4, 0);
        addObject(player);
        //player-> speed = 0.01f;
    }
    else if (skins == Skin::SKIN_KING)
    {
        player = std::make_unique<Player>(gameManager->getAssetManager()->getTexture(GameTexture::Player5), gameManager->getRenderer());
        player->setPosition(positionX, positionY);
        player->setSize(scaledTileSize, scaledTileSize);
        player->setClip(tileSize, tileSize, tileSize * 4, 0);
        addObject(player);
        //player-> speed = 0.01f;
    }
    else if (skins == Skin::SKIN_JASS)
    {
        player = std::make_unique<Player>(gameManager->getAssetManager()->getTexture(GameTexture::Player6), gameManager->getRenderer());
        player->setPosition(positionX, positionY);
        player->setSize(scaledTileSize, scaledTileSize);
        player->setClip(tileSize, tileSize, tileSize * 4, 0);
        addObject(player);
        //player-> speed = 0.01f;
    }
}

void LevelScene::spawnEnemy(GameTexture texture, AIType type, const int positionX, const int positionY)
{
    if (stage == 1)
    {
        auto enemy1 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy1), gameManager->getRenderer());
        enemy1->setPosition(positionX, positionY);
        enemy1->setSize(scaledTileSize, scaledTileSize);
        enemy1->setAIType(type);
        addObject(enemy1);
        enemies.push_back(enemy1);
    }

    else if (stage == 2)
    {
        auto enemy1 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy1), gameManager->getRenderer());
        enemy1->setPosition(positionX, positionY);
        enemy1->setSize(scaledTileSize, scaledTileSize);
        enemy1->setAIType(type);
        addObject(enemy1);
        enemies.push_back(enemy1);


        auto enemy2 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy2), gameManager->getRenderer());
        enemy2->setPosition(positionX, positionY);
        enemy2->setSize(scaledTileSize, scaledTileSize);
        enemy2->setAIType(type);
        addObject(enemy2);
        enemies.push_back(enemy2);
    }
    else if (stage == 3)
    {
        auto enemy1 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy1), gameManager->getRenderer());
        enemy1->setPosition(positionX, positionY);
        enemy1->setSize(scaledTileSize, scaledTileSize);
        enemy1->setAIType(type);
        addObject(enemy1);
        enemies.push_back(enemy1);

        auto enemy2 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy2), gameManager->getRenderer());
        enemy2->setPosition(positionX, positionY);
        enemy2->setSize(scaledTileSize, scaledTileSize);
        enemy2->setAIType(type);
        addObject(enemy2);
        enemies.push_back(enemy2);

        auto enemy3 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy4), gameManager->getRenderer());
        enemy3->setPosition(positionX, positionY);
        enemy3->setSize(scaledTileSize, scaledTileSize);
        enemy3->setAIType(type);
        addObject(enemy3);
        enemies.push_back(enemy3);
    }
    else if (stage == 4)
    {
        auto enemy1 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy1), gameManager->getRenderer());
        enemy1->setPosition(positionX, positionY);
        enemy1->setSize(scaledTileSize, scaledTileSize);
        enemy1->setAIType(type);
        addObject(enemy1);
        enemies.push_back(enemy1);

        auto enemy2 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy2), gameManager->getRenderer());
        enemy2->setPosition(positionX, positionY);
        enemy2->setSize(scaledTileSize, scaledTileSize);
        enemy2->setAIType(type);
        addObject(enemy2);
        enemies.push_back(enemy2);

        auto enemy3 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy4), gameManager->getRenderer());
        enemy3->setPosition(positionX, positionY);
        enemy3->setSize(scaledTileSize, scaledTileSize);
        enemy3->setAIType(type);
        addObject(enemy3);
        enemies.push_back(enemy3);

        auto enemy4 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy3), gameManager->getRenderer());
        enemy4->setPosition(positionX, positionY);
        enemy4->setSize(scaledTileSize, scaledTileSize);
        enemy4->setAIType(type);
        addObject(enemy4);
        enemies.push_back(enemy4);
    }
    else 
    {
        auto enemy1 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy1), gameManager->getRenderer());
        enemy1->setPosition(positionX, positionY);
        enemy1->setSize(scaledTileSize, scaledTileSize);
        enemy1->setAIType(type);
        addObject(enemy1);
        enemies.push_back(enemy1);

        auto enemy2 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy2), gameManager->getRenderer());
        enemy2->setPosition(positionX, positionY);
        enemy2->setSize(scaledTileSize, scaledTileSize);
        enemy2->setAIType(type);
        addObject(enemy2);
        enemies.push_back(enemy2);

        auto enemy3 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy4), gameManager->getRenderer());
        enemy3->setPosition(positionX, positionY);
        enemy3->setSize(scaledTileSize, scaledTileSize);
        enemy3->setAIType(type);
        addObject(enemy3);
        enemies.push_back(enemy3);

        auto enemy4 = std::make_shared<Enemy>(gameManager->getAssetManager()->getTexture(GameTexture::Enemy3), gameManager->getRenderer());
        enemy4->setPosition(positionX, positionY);
        enemy4->setSize(scaledTileSize, scaledTileSize);
        enemy4->setAIType(type);
        addObject(enemy4);
        enemies.push_back(enemy4);
    }
    
}

void LevelScene::generateEnemies()
{
    // we need enemy in random tile
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    auto randCount = std::bind(std::uniform_int_distribution<int>(minEnemiesOnLevel, maxEnemiesOnLevel),
        std::mt19937(static_cast<unsigned int>(seed)));
    auto randType = std::bind(std::uniform_int_distribution<int>(0, 1),
        std::mt19937(static_cast<unsigned int>(seed)));
    auto randTexture = std::bind(std::uniform_int_distribution<int>(0, 2),
        std::mt19937(static_cast<unsigned int>(seed)));
    auto randCellX = std::bind(std::uniform_int_distribution<int>(0, tileArrayHeight - 1),
        std::mt19937(static_cast<unsigned int>(seed)));
    auto randCellY = std::bind(std::uniform_int_distribution<int>(0, tileArrayWidth - 1),
        std::mt19937(static_cast<unsigned int>(seed)));
    // start enemies spawn

 
    for (int i = 0; i < stage; i++)
    {
        // try to find suitable tile
        int cellX = randCellX();
        int cellY = randCellY();
        while (tiles[cellX][cellY] == GameTile::Brick || tiles[cellX][cellY] == GameTile::Stone ||
            tiles[cellX][cellY] == GameTile::EmptyGrass)
        {
            cellX = randCellX();
            cellY = randCellY();
        }
        // spawn enemy
        int textureRand = randTexture();
        spawnEnemy(textureRand == 0 ? GameTexture::Enemy1 :
            (textureRand == 1 ? GameTexture::Enemy2 : GameTexture::Enemy3),
            randType() == 0 ? AIType::wandering : AIType::chasing,
            fieldPositionX + cellY * scaledTileSize, fieldPositionY + cellX * scaledTileSize);
    }
}

void LevelScene::spawnItem(GameTexture texture, const int positionX, const int positionY)
{
    /*if (gameVersion == GameVersion::GAMEVERSION_CARTOON)
    {
        auto item = std::make_shared<Item>(gameManager->getAssetManager()->getTexture(GameTexture::SkullItem), gameManager->getRenderer());
        
        item->setPosition(positionX, positionY);
        item->setSize(scaledTileSize, scaledTileSize);
        addObject(item);
        items.push_back(item);
    }

    else if (gameVersion == GameVersion::GAMEVERSION_CLASIC)
    {
        auto item = std::make_shared<Item>(gameManager->getAssetManager()->getTexture(GameTexture::RayoItem), gameManager->getRenderer());

        item->setPosition(positionX, positionY);
        item->setSize(scaledTileSize, scaledTileSize);
        addObject(item);
        items.push_back(item);
    }

    else if (gameVersion == GameVersion::GAMEVERSION_CUSTOM)
    {
        auto item = std::make_shared<Item>(gameManager->getAssetManager()->getTexture(GameTexture::RelojItem), gameManager->getRenderer());

        item->setPosition(positionX, positionY);
        item->setSize(scaledTileSize, scaledTileSize);
        addObject(item);
        items.push_back(item);
    }
    else if (gameVersion == GameVersion::GAMEVERSION_REALISTIC)
    {
        auto item = std::make_shared<Item>(gameManager->getAssetManager()->getTexture(GameTexture::MedalItem), gameManager->getRenderer());

        item->setPosition(positionX, positionY);
        item->setSize(scaledTileSize, scaledTileSize);
        addObject(item);
        items.push_back(item);
    }*/
}



void LevelScene::generateItems()
{
    //// we need enemy in random tile
    //const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    //auto randCount = std::bind(std::uniform_int_distribution<int>(minItemsOnLevel, maxItemsOnLevel),
    //    std::mt19937(static_cast<unsigned int>(seed)));

    //auto randCellX = std::bind(std::uniform_int_distribution<int>(0, tileArrayHeight - 1),
    //    std::mt19937(static_cast<unsigned int>(seed)));
    //auto randCellY = std::bind(std::uniform_int_distribution<int>(0, tileArrayWidth - 1),
    //    std::mt19937(static_cast<unsigned int>(seed)));
    //// start enemies spawn
    //for (int i = 0; i < randCount(); i++)
    //{
    //    // try to find suitable tile
    //    int cellIX = randCellX();
    //    int cellIY = randCellY();
    //    while (tiles[cellIX][cellIY] == GameTile::Grass)
    //    {
    //        cellIX = randCellX();
    //        cellIY = randCellY();
    //    }
    //    // spawn item
    //    if (gameVersion == GameVersion::GAMEVERSION_CARTOON) 
    //    {
    //        spawnItem(GameTexture::SkullItem,
    //        fieldPositionX + cellIY * scaledTileSize, fieldPositionY + cellIX * scaledTileSize);

    //    }
    //    else if (gameVersion == GameVersion::GAMEVERSION_CLASIC)
    //    {
    //        spawnItem(GameTexture::RayoItem,
    //            fieldPositionX + cellIY * scaledTileSize, fieldPositionY + cellIX * scaledTileSize);
    //    }
    //    else if (gameVersion == GameVersion::GAMEVERSION_CUSTOM)
    //    {
    //        spawnItem(GameTexture::RelojItem,
    //            fieldPositionX + cellIY * scaledTileSize, fieldPositionY + cellIX * scaledTileSize);
    //    }
    //    else if (gameVersion == GameVersion::GAMEVERSION_REALISTIC)
    //    {
    //        spawnItem(GameTexture::MedalItem,
    //            fieldPositionX + cellIY * scaledTileSize, fieldPositionY + cellIX * scaledTileSize);
    //    }
    //}
}

void LevelScene::spawnBomb(GameGraphicObject* object)
{
    // we can only have 1 bomb and should have object
    if(bomb || !object)
    {
        return;
    }
    // calculate position
    int bombPositionX = object->getPositionX();
    int bombPositionY = object->getPositionY() - fieldPositionY;
    const int bombPositionDiffX = bombPositionX % scaledTileSize;
    const int bombPositionDiffY = bombPositionY % scaledTileSize;
    // set bomb in strongly in cell
    bombPositionX = (bombPositionDiffX > scaledTileSize / 2) ?
                        bombPositionX + scaledTileSize - bombPositionDiffX :
                        bombPositionX - bombPositionDiffX;
    bombPositionY = (bombPositionDiffY > scaledTileSize / 2) ?
                        bombPositionY + scaledTileSize - bombPositionDiffY :
                        bombPositionY - bombPositionDiffY;
    bombPositionY += fieldPositionY;
    // create bomb in position
    bomb =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::Bomb), gameManager->getRenderer());
    bomb->setSize(scaledTileSize, scaledTileSize);
    bomb->setPosition(bombPositionX, bombPositionY);
    insertObject(bomb, backgroundObjectLastNumber);
    // animation
    auto animation = std::make_shared<Animation>();
    animation->addAnimationEntity(AnimationEntity(0, 0, tileSize, tileSize));
    animation->addAnimationEntity(AnimationEntity(tileSize * 1, 0, tileSize, tileSize));
    animation->addAnimationEntity(AnimationEntity(tileSize * 2, 0, tileSize, tileSize));
    animation->addAnimationEntity(AnimationEntity(tileSize * 3, 0, tileSize, tileSize));
    animation->setSprite(bomb.get());
    bomb->addAnimation(animation);
    // change to bomb
    const int bombCellX = static_cast<int>(
        round((bomb->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int bombCellY = static_cast<int>(
        round((bomb->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[bombCellY][bombCellX] = GameTile::Bomb;
    // update timer
    bombTimer = bombTimerStart;
    animation->play();
}

void LevelScene::spawnBang(GameGraphicObject* object)
{
    // change to grass
    const int bombCellX = static_cast<int>(
        round((bomb->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int bombCellY = static_cast<int>(
        round((bomb->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[bombCellY][bombCellX] = GameTile::Grass;
    // create bangs in position
    for(unsigned int i = 0; i < bangSpawnCells; i++)
    {
        auto bang = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::Explosion),
                                                gameManager->getRenderer());
        bang->setSize(scaledTileSize, scaledTileSize);
        bang->setPosition(object->getPositionX() + bangSpawnPositions[i][0] * scaledTileSize,
                            object->getPositionY() + bangSpawnPositions[i][1] * scaledTileSize);
        addObject(bang);
        bangs.push_back(bang);
        // change to bang
        const int bangCellX = static_cast<int>(
            round((bang->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
        const int bangCellY = static_cast<int>(
            round((bang->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
        tiles[bangCellY][bangCellX] = GameTile::Bang;
        // animation
        auto animation = std::make_shared<Animation>();
        for(unsigned int j = 1; j < 12; j++)
        {
            animation->addAnimationEntity(AnimationEntity(tileSize * j, 0, tileSize, tileSize));
        }
        animation->setSprite(bang.get());
        bang->addAnimation(animation);
        animation->play();
        explosionSound->play();
    }
    // update timer
    bangTimer = bangTimerStart;
}

void LevelScene::spawnDoor(GameGraphicObject* object)
{
    // create door in position
    door =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::Door), gameManager->getRenderer());
    door->setSize(scaledTileSize, scaledTileSize);
    door->setPosition(object->getPositionX(), object->getPositionY());
    insertObject(door, backgroundObjectLastNumber);
}

void LevelScene::spawnDoorItemTP(GameGraphicObject* objectItem)
{
    // create door in position
    doorItemTP =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::TpItem), gameManager->getRenderer());
    doorItemTP->setSize(scaledTileSize, scaledTileSize);
    doorItemTP->setPosition(objectItem->getPositionX(), objectItem->getPositionY());
    insertObject(doorItemTP, backgroundObjectLastNumber);
}


//ITEM VIDA 
void LevelScene::spawnDoorItemV(GameGraphicObject* objectItemv)
{
    // create door in position
    doorItemV =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::HeartItem), gameManager->getRenderer());
    doorItemV->setSize(scaledTileSize, scaledTileSize);
    doorItemV->setPosition(objectItemv->getPositionX(), objectItemv->getPositionY());
    insertObject(doorItemV, backgroundObjectLastNumber);
}

//ITEM ANTIVIDA
void LevelScene::spawnDoorItemAV(GameGraphicObject* objectItemav)
{
    // create door in position
    doorItemAV =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::SkullItem), gameManager->getRenderer());
    doorItemAV->setSize(scaledTileSize, scaledTileSize);
    doorItemAV->setPosition(objectItemav->getPositionX(), objectItemav->getPositionY());
    insertObject(doorItemAV, backgroundObjectLastNumber);
}


//ITEM TIEMPO
void LevelScene::spawnDoorItemT(GameGraphicObject* objectItemt)
{
    // create door in position
    doorItemT =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::RelojItem), gameManager->getRenderer());
    doorItemT->setSize(scaledTileSize, scaledTileSize);
    doorItemT->setPosition(objectItemt->getPositionX(), objectItemt->getPositionY());
    insertObject(doorItemT, backgroundObjectLastNumber);
}


//ITEM ANTI TIEMPO
void LevelScene::spawnDoorItemAT(GameGraphicObject* objectItemat)
{
    // create door in position
    doorItemAT =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::HourglassItem), gameManager->getRenderer());
    doorItemAT->setSize(scaledTileSize, scaledTileSize);
    doorItemAT->setPosition(objectItemat->getPositionX(), objectItemat->getPositionY());
    insertObject(doorItemAT, backgroundObjectLastNumber);
}


//ITEM TORTUGA
void LevelScene::spawnDoorItemTort(GameGraphicObject* objectItemtt)
{
    // create door in position
    doorItemTort =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::TurtleItem), gameManager->getRenderer());
    doorItemTort->setSize(scaledTileSize, scaledTileSize);
    doorItemTort->setPosition(objectItemtt->getPositionX(), objectItemtt->getPositionY());
    insertObject(doorItemTort, backgroundObjectLastNumber);
}


//ITEM VELOCIDAD
void LevelScene::spawnDoorItemVD(GameGraphicObject* objectItemvd)
{
    // create door in position
    doorItemVD =
        std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::RayoItem), gameManager->getRenderer());
    doorItemVD->setSize(scaledTileSize, scaledTileSize);
    doorItemVD->setPosition(objectItemvd->getPositionX(), objectItemvd->getPositionY());
    insertObject(doorItemVD, backgroundObjectLastNumber);
}

void LevelScene::finish() const
{
    menuMusic->stop();
    if(isWin)
    {
        winSound->play();
        gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, stage + 1, score));
        gameManager->getSceneManager()->activateScene("stage");
    }
    else
    {
        gameoverSound->play();
        gameManager->getSceneManager()->activateScene("gameover");
    }
    gameManager->getSceneManager()->removeScene("level");
}

void LevelScene::gameOver()
{
    menuMusic->stop();
    gameOverTimer = gameOverTimerStart;
    isGameOver = true;
}


void LevelScene::exit() const
{
    menuMusic->stop();
    gameManager->getSceneManager()->activateScene("menu");
    gameManager->getSceneManager()->removeScene("level");
}

void LevelScene::onEvent(const SDL_Event& event)
{
    Scene::onEvent(event);
    // we need to update movement if movement keys pressed or released
    if((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
    {
        updateMovement(event.type == SDL_KEYDOWN ? true : false, event.key.keysym.scancode);
    }

    if(event.type == SDL_KEYDOWN)
    {
        // we should go to main menu by Escape key
        if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            gameOver();
            isWin = false;
            gameOverTimer = winTimerStart;
        }
        // we can spawn a bomb by space press
        else if(event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            if(!isGameOver)
            {
                spawnBomb(player.get());
            }
        }
        // we can pause a gameManager by pressing enter key
        else if(event.key.keysym.scancode == SDL_SCANCODE_RETURN)
        {
            isPaused = !isPaused;
            if(isPaused)
            {
                menuMusic->pause();
            }
            else
            {
                menuMusic->resume();
            }
        }
        // stage complete cheat
        else if(event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
        {
            gameOver();
            isWin = true;
            score += scoreRewardForStage * 100;
            gameOverTimer = winTimerStart;
        }
    }
}

void LevelScene::update(const unsigned int delta)
{
    // pause
    if(isPaused)
    {
        return;
    }
    Scene::update(delta);
    // update collision of player
    updatePlayerCollision();
    // update collision of enemies
    updateEnemiesCollision();
    // update collision of items
    updateItemsCollision();
    // update collision of bricks
    updateBangsCollision();
    // update camera
    updateCamera();
    // update timers
    updateTimers(delta);
}

void LevelScene::updateTimers(const unsigned int delta)
{
    // update level timer
    levelTimer -= delta;
    levelTimerDelta += delta;
    if(levelTimerDelta >= levelTimerUpdateText)
    {
        updateLevelTimer();
    }
    // update bomb timer
    if(bomb != nullptr)
    {
        updateBombTimer(delta);
    }
    // update bang timer
    if(bangs.size() > 0)
    {
        updateBangTimer(delta);
    }
    // update gameManager over timer
    if(isGameOver)
    {
        updateGameOverTimer(delta);
    }

    // finish level if level timer is 0
    if(levelTimer <= 0 && !isGameOver)
    {
        gameOver();
        isWin = false;
        gameOverTimer = winTimerStart;
    }
}

void LevelScene::updateLevelTimer()
{
    if(levelTimer < 0)
    {
        return;
    }
    levelTimerDelta = 0;
    const int timeInSec = static_cast<int>(levelTimer / 1000.0f);
    std::string timeString = std::to_string(timeInSec);
    while(timeString.size() < 3)
    {
        timeString = "0" + timeString;
    }
    timerNumber->setText(timeString);
}

void LevelScene::updateBombTimer(const unsigned int delta)
{
    if(bombTimer > 0)
    {
        bombTimer -= delta;
    }
    else
    {
        spawnBang(bomb.get());
        removeObject(bomb);
        bomb = nullptr;
    }
}

void LevelScene::updateBangTimer(const unsigned int delta)
{
    if(bangTimer > 0)
    {
        bangTimer -= delta;
    }
    else
    {
        for(auto& bang : bangs)
        {
            removeObject(bang);
            // change to grass
            const int bangCellX = static_cast<int>(
                round((bang->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
            const int bangCellY = static_cast<int>(
                round((bang->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
            tiles[bangCellY][bangCellX] = baseTiles[bangCellY][bangCellX];
        }
        bangs.clear();
    }
}

void LevelScene::updateGameOverTimer(const unsigned int delta)
{
    if(gameOverTimer > 0)
    {
        gameOverTimer -= delta;
    }
    else
    {
        finish();
    }
}

void LevelScene::updateMovement(const bool isPressed, const int keycode)
{
    if(player == nullptr)
    {
        return;
    }
    // on press we start movement
    if(isPressed)
    {
        switch(keycode)
        {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                playerDirectionY -= 1;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                playerDirectionY += 1;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                playerDirectionX -= 1;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                playerDirectionX += 1;
                break;
            default:
                break;
        }
    }
    // on release we stop moving
    else
    {
        switch(keycode)
        {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                playerDirectionY += 1;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                playerDirectionY -= 1;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                playerDirectionX += 1;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                playerDirectionX -= 1;
                break;
            default:
                break;
        }
    }
    // depend on pressed key choose player's direction
    MovementDirection direction = MovementDirection::None;
    if(playerDirectionX != 0)
    {
        if(playerDirectionX > 0)
        {
            direction = MovementDirection::Right;
        }
        else
        {
            direction = MovementDirection::Left;
        }
    }
    else if(playerDirectionY != 0)
    {
        if(playerDirectionY > 0)
        {
            direction = MovementDirection::Down;
        }
        else
        {
            direction = MovementDirection::Up;
        }
    }
    // apply direction
    player->setMovementDirection(direction);
}

void LevelScene::updateCamera()
{
    if(player == nullptr)
    {
        return;
    }
    // consts for camera checking
    const int screenStart = fieldPositionX;
    const int screenFinish = fieldPositionX + scaledTileSize * static_cast<int>(tileArrayWidth);
    const int screenWidthHalf = gameManager->getWindowWidth() / 2;
    int cameraPositionX = player->getPositionX();
    // check borders of screen
    if(cameraPositionX <= screenWidthHalf)
    {
        cameraPositionX = screenStart;
    }
    else if(cameraPositionX + screenWidthHalf >= screenFinish)
    {
        cameraPositionX = screenFinish - gameManager->getWindowWidth();
    }
    else
    {
        cameraPositionX -= screenWidthHalf;
    }
    // time to move camera
    setCamera(cameraPositionX, 0);
}

void LevelScene::updateScore()
{
    std::string scoreText = std::to_string(score);
    scoreNumber->setText(scoreText);
    scoreNumber->setSize(static_cast<int>(timerNumber->getWidth() / 3.0f) *
                                static_cast<int>(scoreText.size()),
                            scoreNumber->getHeight());
    scoreNumber->setPosition(480, 10);
}

void LevelScene::updateVida()
{
    std::string vidasText = std::to_string(vida);
    vidasNumber->setText(vidasText);
    vidasNumber->setSize(static_cast<int>(timerNumber->getWidth() / 3.0f) *
        static_cast<int>(vidasText.size()),
        vidasNumber->getHeight());
    vidasNumber->setPosition(180, 10);
}

void LevelScene::updatePlayerCollision()
{
    if (player == nullptr)
    {
        return;
    }
    // there is no reason to check collision if player is idle
    if (!player->isMoving())
    {
        return;
    }
    // set width to smaller size for easer pa th
    SDL_Rect playerRect = player->getRect();
    playerRect.w = static_cast<int>(playerRect.w * 0.5);
    playerRect.h = static_cast<int>(playerRect.h * 0.5);
    // iterate objects for collision
    for (const auto& collisionObject : collisions)
    {
        if (isCollisionDetected(playerRect, collisionObject.second->getRect()))
        {
            player->revertLastMove();
        }
    }

    if (door != nullptr)
    {
        if (isCollisionDetected(playerRect, door->getRect()))
        {
            // check win condition
            if (!isGameOver && enemies.size() == 0)
            {
                gameOver();
                isWin = true;
                score += scoreRewardForStage;
                gameOverTimer = winTimerStart;

            }
        }
    }

    //teletransporta a bomberman
    if (doorItemTP != nullptr)
    {
        if (isCollisionDetected(playerRect, doorItemTP->getRect()))
        {
            removeObject(doorItemTP);
            removeObject(player);
            spawnPlayer(fieldPositionX + 1 * scaledTileSize,
                fieldPositionY + 13 * scaledTileSize);
            doorItemTP = nullptr;
            itemTeleportSound->play();
        }
    }

    //da más una vida a bomberman
    if (doorItemV != nullptr)
    {
        if (isCollisionDetected(playerRect, doorItemV->getRect()))
        {
            removeObject(doorItemV);
            vida = vida + 1;
            doorItemV = nullptr;
            updateVida();
            itemVidaSound->play();
        }
    }


    //le quita una vida a bomberman
    if (doorItemAV != nullptr)
    {
        if (isCollisionDetected(playerRect, doorItemAV->getRect()))
        {
            removeObject(doorItemAV);
            vida = vida - 1;
            doorItemAV = nullptr;
            updateVida();
            removeObject(player);
            spawnPlayer(fieldPositionX + playerStartX * scaledTileSize,
                fieldPositionY + playerStartY * scaledTileSize);
            itemAntiVidaSound->play();
        }
    }

    // aumenta tiempo de partida
    if (doorItemT != nullptr)
    {
        if (isCollisionDetected(playerRect, doorItemT->getRect()))
        {
            levelTimer = levelTimer + 10000;
            removeObject(doorItemT);
            doorItemT = nullptr;
            itemTiempoSound->play();
        }
    }

    // disminuye tiempo de partida
    if (doorItemAT != nullptr)
    {
        if (isCollisionDetected(playerRect, doorItemAT->getRect()))
        {
            levelTimer = levelTimer - 10000; 
            removeObject(doorItemAT); 
            doorItemAT = nullptr;
            itemAntiTiempoSound->play();
        }
    }


    // player disminuye velocidad
    if (doorItemTort != nullptr)
    {
        if (isCollisionDetected(playerRect, doorItemTort->getRect()))
        {
            removeObject(doorItemTort);
            player->speed = 0.003f;
            doorItemTort = nullptr;
            itemTortugaSound->play();
        }
    }
    

    // player aumenta velocidad
    if (doorItemVD != nullptr)
    {
        if (isCollisionDetected(playerRect, doorItemVD->getRect()))
        {
            removeObject(doorItemVD);
            player->speed = 0.02f;
            doorItemVD = nullptr;
            itemVelocidadSound->play();
        }
    }
}

void LevelScene::updateEnemiesCollision()
{
    // iterate enemies for collision
    for(const auto& enemy : enemies)
    {
        // iterate drawables for collision
        for(const auto& collisionObject : collisions)
        {
            // check for block collision
            if(isCollisionDetected(enemy->getRect(), collisionObject.second->getRect()))
            {
                // stop moving on collision detection
                enemy->setMoving(false);
                enemy->revertLastMove();
            }
        }
        // check for bomb collision
        if(bomb && isCollisionDetected(enemy->getRect(), bomb->getRect()))
        {
            // stop moving on collision detection
            enemy->setMoving(false);
            enemy->revertLastMove();
        }
        // check for player collision
        if(player != nullptr)
        {
            // set width to smaller size
            SDL_Rect playerRect = player->getRect();
            playerRect.w = static_cast<int>(playerRect.w * 0.2);
            playerRect.h = static_cast<int>(playerRect.h * 0.2);
            if(isCollisionDetected(playerRect, enemy->getRect()))
            {
                vida = vida - 1;
                std::cout << vida << std::endl;
                removeObject(player);
                spawnPlayer(fieldPositionX + playerStartX * scaledTileSize, fieldPositionY + playerStartY * scaledTileSize);
                updateVida();
            }

            if (vida == 0)
            {
                removeObject(player);
                player = nullptr;
                gameOver();
            }
        }
        if(player != nullptr)
        {
            // can attack?
            if(!enemy->isMovingToCell() && enemy->canAttack())
            {
                // check for attack radius
                if(abs(player->getPositionX() + player->getWidth() / 2 - enemy->getPositionX() -
                        enemy->getWidth() / 2) < enemy->getAttackRadius() &&
                    abs(player->getPositionY() + player->getHeight() / 2 - enemy->getPositionY() -
                        enemy->getHeight() / 2) < enemy->getAttackRadius())
                {
                    // start follow to player
                    followToPlayer(enemy.get());
                }
            }
        }
    }
}

void LevelScene::updateItemsCollision()
{
    // iterate enemies for collision
    //for (const auto& item : items)
    //{
    //    
    //    
    //    // check for player collision
    //    if (player != nullptr)
    //    {
    //        // set width to smaller size
    //        SDL_Rect playerRect = player->getRect();
    //        playerRect.w = static_cast<int>(playerRect.w * 0.2);
    //        playerRect.h = static_cast<int>(playerRect.h * 0.2);
    //        if (isCollisionDetected(playerRect, item->getRect()))
    //        {
    //            if (gameVersion == GameVersion::GAMEVERSION_CARTOON) 
    //            {
    //                // player killed by skullitem
    //                removeObject(player);
    //                player = nullptr;
    //                gameOver();
    //            }
    //            else if (gameVersion == GameVersion::GAMEVERSION_CLASIC)
    //            {
    //                // player aumenta velocidad
    //                removeObject(item);
    //                player->speed = 0.02f;
    //            }
    //            else if (gameVersion == GameVersion::GAMEVERSION_CUSTOM)
    //            {
    //                // aumenta tiempo tiempo de partida
    //                removeObject(item);
    //                levelTimer= levelTimer + 100;
    //            }
    //            else if (gameVersion == GameVersion::GAMEVERSION_REALISTIC)
    //            {
    //                // player cambia de skin
    //                removeObject(item);
    //                gameManager->getSceneManager()->activateScene("you win");
    //            }
    //            
    //        }
    //    }
    //    
    //}
}

void LevelScene::updateBangsCollision()
{
    // check for bang collision
    for(const auto& bang : bangs)
    {
        // check bricks
        auto itCollision = collisions.begin();
        while(itCollision != collisions.end())
        {
            if((*itCollision).first == GameTile::Brick)
            {
                auto brick = (*itCollision).second;
                if(isCollisionDetected(brick->getRect(), bang->getRect()))
                {
                    destroyBrick(brick);
                    destroyBrickTP(brick);
                    destroyBrickV(brick);
                    destroyBrickAV(brick);
                    destroyBrickT(brick);
                    destroyBrickAT(brick);
                    destroyBrickTort(brick);
                    destroyBrickVD(brick);
                    // remove brick from collision array
                    itCollision = collisions.erase(itCollision);
                    continue;
                }
            }
            ++itCollision;
        }
        // check enemies
        auto itEnemies = enemies.begin();
        while(itEnemies != enemies.end())
        {
            SDL_Rect enemyRect = (*itEnemies)->getRect();
            enemyRect.w = static_cast<int>(enemyRect.w * 0.2);
            enemyRect.h = static_cast<int>(enemyRect.h * 0.2);
            if(isCollisionDetected(enemyRect, bang->getRect()))
            {
                removeObject(*itEnemies);
                itEnemies = enemies.erase(itEnemies);

                // enemy killed by bang
                score += scoreRewardForKill;
                updateScore();
                continue;
            }
            ++itEnemies;
        }
        // check player
        /*if(player != nullptr)
        {
            SDL_Rect playerRect = player->getRect();
            playerRect.w = static_cast<int>(playerRect.w * 0.2f);
            playerRect.h = static_cast<int>(playerRect.h * 0.2f);
            if(isCollisionDetected(playerRect, bang->getRect()))
            {
                removeObject(player);
                player = nullptr;
                gameOver();
            }
        }*/

        // check player
        if (player != nullptr)
        {
            //int vida = 3;
            SDL_Rect playerRect = player->getRect();
            playerRect.w = static_cast<int>(playerRect.w * 0.2f);
            playerRect.h = static_cast<int>(playerRect.h * 0.2f);


            if (isCollisionDetected(playerRect, bang->getRect()))
            {
                vida = vida - 1;
                std::cout << vida << std::endl;
                removeObject(player);
                spawnPlayer(fieldPositionX + playerStartX * scaledTileSize, fieldPositionY + playerStartY * scaledTileSize);
                updateVida();
            }
            if (vida == 0)
            {
                removeObject(player);
                player = nullptr;
                gameOver();
            }
            
        }
    }
}

bool LevelScene::isCollisionDetected(const SDL_Rect& rect1, const SDL_Rect& rect2) const
{
    // check for collision
    if(rect1.x + rect1.w / 2 <= rect2.x - rect2.w / 2)
        return false;
    if(rect1.x - rect1.w / 2 >= rect2.x + rect2.w / 2)
        return false;
    if(rect1.y + rect1.h / 2 <= rect2.y - rect2.h / 2)
        return false;
    if(rect1.y - rect1.h / 2 >= rect2.y + rect2.h / 2)
        return false;

    return true;
}

void LevelScene::destroyBrick(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if(door == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
                                            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoor = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomize),
                                    std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if(randDoor() == 0 || bricksCount <= 1)
        {
            spawnDoor(brick.get());
        }
    }
    // change brick to grass and remove it
    const int brickCellX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellY][brickCellX] = GameTile::Grass;
    removeObject(brick);
}


void LevelScene::destroyBrickTP(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if (doorItemTP == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoorItem = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomizeItem),
            std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoorItem() == 0 || bricksCount <= 1)
        {
            spawnDoorItemTP(brick.get());
            //  brickSpawnRandomize

        }
    }
    // change brick to grass and remove it
    const int brickCellXX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellYY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellYY][brickCellXX] = GameTile::Grass;
    removeObject(brick);
}





void LevelScene::destroyBrickV(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if (doorItemV == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoorItem = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomizeItem),
            std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoorItem() == 0 || bricksCount <= 1)
        {
            spawnDoorItemV(brick.get());
            //  brickSpawnRandomize

        }
    }
    // change brick to grass and remove it
    const int brickCellXX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellYY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellYY][brickCellXX] = GameTile::Grass;
    removeObject(brick);
}


void LevelScene::destroyBrickAV(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if (doorItemAV == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoorItem = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomizeItem),
            std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoorItem() == 0 || bricksCount <= 1)
        {
            spawnDoorItemAV(brick.get());
            //  brickSpawnRandomize

        }
    }
    // change brick to grass and remove it
    const int brickCellXX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellYY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellYY][brickCellXX] = GameTile::Grass;
    removeObject(brick);
}



void LevelScene::destroyBrickT(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if (doorItemT == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoorItem = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomizeItem),
            std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoorItem() == 0 || bricksCount <= 1)
        {
            spawnDoorItemT(brick.get());
            //  brickSpawnRandomize

        }
    }
    // change brick to grass and remove it
    const int brickCellXX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellYY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellYY][brickCellXX] = GameTile::Grass;
    removeObject(brick);
}



void LevelScene::destroyBrickAT(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if (doorItemAT == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoorItem = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomizeItem),
            std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoorItem() == 0 || bricksCount <= 1)
        {
            spawnDoorItemAT(brick.get());
            //  brickSpawnRandomize

        }
    }
    // change brick to grass and remove it
    const int brickCellXX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellYY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellYY][brickCellXX] = GameTile::Grass;
    removeObject(brick);
}


void LevelScene::destroyBrickTort(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if (doorItemTort == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoorItem = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomizeItem),
            std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoorItem() == 0 || bricksCount <= 1)
        {
            spawnDoorItemTort(brick.get());
            //  brickSpawnRandomize

        }
    }
    // change brick to grass and remove it
    const int brickCellXX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellYY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellYY][brickCellXX] = GameTile::Grass;
    removeObject(brick);
}



void LevelScene::destroyBrickVD(std::shared_ptr<GameGraphicObject> brick)
{
    // we need door if don't have
    if (doorItemVD == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
            [](auto collision) { return collision.first == GameTile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoorItem = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomizeItem),
            std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoorItem() == 0 || bricksCount <= 1)
        {
            spawnDoorItemVD(brick.get());
            //  brickSpawnRandomize

        }
    }
    // change brick to grass and remove it
    const int brickCellXX = static_cast<int>(
        round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int brickCellYY = static_cast<int>(
        round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    tiles[brickCellYY][brickCellXX] = GameTile::Grass;
    removeObject(brick);
}

void LevelScene::followToPlayer(Enemy* enemy)
{
    // move to nearest cell if enemy is wandering
    if(enemy->isMoving())
    {
        std::pair<int, int> cell = std::make_pair(0, 0);
        enemy->moveToCell(cell);
        return;
    }
    // get cells of creatures by their position
    const int playerCellX = static_cast<int>(
        round((player->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int playerCellY = static_cast<int>(
        round((player->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
    const int enemyCellX = static_cast<int>(
        round((enemy->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
    const int enemyCellY = static_cast<int>(
        round((enemy->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));

    // Source is the left-most bottom-most corner
    std::pair<unsigned int, unsigned int> src = std::make_pair(enemyCellY, enemyCellX);

    // Destination is the left-most top-most corner
    std::pair<unsigned int, unsigned int> dest = std::make_pair(playerCellY, playerCellX);

    // get best nearest cell to follow
    std::pair<int, int> cell = findBestCell(tiles, src, dest);
    if(cell.first >= 0 && cell.second >= 0)
    {
        cell.first -= src.first;
        cell.second -= src.second;
        enemy->moveToCell(cell);
    }
    else
    {
        enemy->generateNewPath();
    }
}

bool LevelScene::crearObjetosJuego(string _path)
{
    // Crea un flujo de archivo
    fstream file;

    // Abrir el archivo
    file.open(_path.c_str(), ios::in);

    if (file.is_open() == false) {
    	std::cout << "No se pudo abrir el archivo de mapa" << std::endl;
    	return false;
    }

    string line;
    
    tileGraph = new TileGraph(25, 15);
    GameObjectPacman::tileGraph = tileGraph;
    Texture::Renderer = gameManager->getRenderer();
   
    int x = 0;
    int y = 0;
    
    while (getline(file, line)) {
    	vector<char> chars(line.begin(), line.end());
    	x = 0;

    	for (int i = 0; i < chars.size(); i++) {
    		if (chars[i] != ' ') {
    			Tile* tile = tileGraph->GetTileAt(x, y);
                
    			switch (chars[i]) {
    			case '0':
                    spawnGrass(fieldPositionX + x * scaledTileSize, fieldPositionY + y * scaledTileSize);
    				break;
    			case '1':
                    spawnGrass(fieldPositionX + x * scaledTileSize, fieldPositionY + y * scaledTileSize);
                    spawnBrick(fieldPositionX + x * scaledTileSize, fieldPositionY + y * scaledTileSize);
                    break;
    			case '2':
                    spawnStone(fieldPositionX + x * scaledTileSize, fieldPositionY + y * scaledTileSize);
                    //spawnWallPacman(fieldPositionX + x * scaledTileSize, fieldPositionY + y * scaledTileSize, tile);
       				break;
    			}
                x++;
    		}
    	}
    	y++;
    }

    return false;
}
