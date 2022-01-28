#ifndef _BOMBERMAN_CONST_H_
#define _BOMBERMAN_CONST_H_
/**
 * @brief Tiles class for tile map creation
 *
 */
enum class GameTile
{
    Stone,
    Wall,
    Item,
    Grass,
    Brick,
    EmptyGrass,
    Bomb,
    Bang
};

const int playerStartX = 1; // player start position X on tilemap
const int playerStartY = 1; // player start position Y on tilemap

const unsigned int brickSpawnRandomize = 10; // less value => more bricks
const unsigned int doorSpawnRandomize = 10;  // less value => door is far
const unsigned int doorSpawnRandomizeItem = 10;
const unsigned int bangSpawnCells = 5;       // bang spawn number of cells

//const unsigned int minEnemiesOnLevel = 2;    // minimum enemies count on level
//const unsigned int maxEnemiesOnLevel = 10;   // maximum enemies count on level

const unsigned int minItemsOnLevel = 5;    // minimum items count on level
const unsigned int maxItemsOnLevel = 8;   // maximum items count on level
const int bangSpawnPositions[bangSpawnCells][2] = {{0, 0},
                                                   {0, 1},
                                                   {1, 0},
                                                   {0, -1},
                                                   {-1, 0}}; // cell's position of bang

const unsigned int tileArrayWidth = 25;                   // tile array width
const unsigned int tileArrayHeight = 15;                  // tile array height
const unsigned int tileSize = 16;                         // size in pixels of tile
//const GameTile baseTiles[tileArrayHeight][tileArrayWidth] = { // base tilemap
const GameTile baseTiles[13][31] = { // base tilemap
    {GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone,
     GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone,
     GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone,
     GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone},
    {GameTile::Stone, GameTile::EmptyGrass, GameTile::EmptyGrass, GameTile::EmptyGrass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Grass,      GameTile::Grass,      GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Grass,      GameTile::Grass,      GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Grass,      GameTile::Grass,      GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Stone},
    {GameTile::Stone, GameTile::EmptyGrass, GameTile::Stone, GameTile::EmptyGrass, GameTile::Stone, GameTile::Grass, GameTile::Stone,
     GameTile::Grass, GameTile::Stone,      GameTile::Grass, GameTile::Stone,      GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass,      GameTile::Stone, GameTile::Grass,      GameTile::Stone, GameTile::Grass, GameTile::Stone,
     GameTile::Grass, GameTile::Stone,      GameTile::Grass, GameTile::Stone,      GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass,      GameTile::Stone},
    {GameTile::Stone, GameTile::EmptyGrass, GameTile::EmptyGrass, GameTile::EmptyGrass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Grass,      GameTile::Grass,      GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Grass,      GameTile::Grass,      GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Grass,      GameTile::Grass,      GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass,      GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Brick, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass,
     GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass,
     GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Grass, GameTile::Stone},
    {GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone,
     GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone,
     GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone,
     GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone, GameTile::Stone}};

#endif // _BOMBERMAN_CONST_H_
