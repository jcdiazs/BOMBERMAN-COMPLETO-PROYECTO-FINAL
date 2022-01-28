#pragma once
#include "Builder.h"
class BuilderCartoon :
    public Builder
{
	virtual std::shared_ptr<Player> getPlayer();
	virtual std::shared_ptr<Enemy> getEnemy();
	virtual vector< std::shared_ptr<Enemy>> getEnemies();
};

