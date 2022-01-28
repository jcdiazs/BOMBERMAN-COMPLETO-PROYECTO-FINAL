#pragma once
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"
#include <SDL.h>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Builder
{

public:
	virtual std::shared_ptr<Player> getPlayer() = 0;
	virtual std::shared_ptr<Enemy> getEnemy() = 0;
	virtual vector<std::shared_ptr<Enemy>> getEnemies() = 0;
};

