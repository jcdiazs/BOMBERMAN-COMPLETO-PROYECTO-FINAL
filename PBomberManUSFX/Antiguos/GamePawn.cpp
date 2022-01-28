#include "GamePawn.h"

GamePawn::GamePawn():GameActor(), keyboardInput(KeyboardInput::Instance())
{

}

GamePawn::GamePawn(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual):
	GameActor(_texture, _renderer, _tileActual) {
	keyboardInput = KeyboardInput::Instance();
}


GamePawn::~GamePawn()
{
}

void GamePawn::render(SDL_Rect& _camera)
{
	GameActor::render(_camera);
}

void GamePawn::update(const unsigned int _delta)
{
	GameActor::update(_delta);
}

void GamePawn::deleteGameObjet()
{
	GameActor::deleteGameObject();
}
