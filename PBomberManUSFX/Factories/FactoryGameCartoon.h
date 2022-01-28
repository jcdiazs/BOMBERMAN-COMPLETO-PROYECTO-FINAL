#pragma once
#include "Factory.h"
#include <SDL.h>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "../Const.h"
#include "../Entities/Enemy.h"
#include "../Entities/CartoonEnemy.h"
#include "../Entities/Music.h"
#include "../Entities/CartoonPlayer.h"
#include "../Entities/Sound.h"
#include "../Entities/Text.h"
#include "../Scenes/Scene.h"
#include "../GameManager.h"
#include "../Managers/AssetManager.h"
#include "../GameAITypes.h"
#include "../GameTextures.h"
#include "../Factories/Factory.h"



class FactoryGameCartoon :
    public Factory
{
private:
    GameManager* gameManager;
    int scaledTileSize;

public:
    FactoryGameCartoon();

    std::shared_ptr<GameObject> CreatePlayer(const int _positionX, const int _positionY);
    std::shared_ptr<GameObject> CreateEnemy(AIType _type, const int _positionX, const int _positionY);
};

