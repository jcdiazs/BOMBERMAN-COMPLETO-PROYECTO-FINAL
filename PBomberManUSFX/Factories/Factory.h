#pragma once
#include "../Entities/GameObject.h"
#include "../GameAITypes.h"
#include "../GameTextures.h"

class Factory
{
//protected:
//	GameManager* gameManager;
public:
	virtual std::shared_ptr<GameObject> CreatePlayer(const int _positionX, const int _positionY) = 0;
	virtual std::shared_ptr<GameObject> CreateEnemy(AIType _type, const int _positionX, const int _positionY) = 0;
	//virtual std::shared_ptr<GameObject> CreateWall(const int _positionX, const int _positionY) = 0;
};

