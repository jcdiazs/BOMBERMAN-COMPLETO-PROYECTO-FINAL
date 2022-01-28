#include "GameObjectPacman.h"

TileGraph* GameObjectPacman::tileGraph = nullptr;

void GameObjectPacman::HandleEvents(SDL_Event* event) {}
void GameObjectPacman::Update() {}
void GameObjectPacman::Render() {}
void GameObjectPacman::Free() {}
SDL_Rect GameObjectPacman::GetCollider() { return { 0,0,0,0 }; }
GameObjectPacman::~GameObjectPacman() {}

 
void GameObjectPacman::Delete()
{
	toDelete = true;
}

bool GameObjectPacman::ToDelete() const
{
	return toDelete;
};