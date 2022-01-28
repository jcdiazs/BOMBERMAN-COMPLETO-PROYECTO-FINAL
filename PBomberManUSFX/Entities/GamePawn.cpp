#include "GamePawn.h"


GamePawn::GamePawn(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer):GameActor(_texture, _renderer) {
	keyboardInput = KeyboardInput::Instance();
};


GamePawn::~GamePawn()
{
}

void GamePawn::render(SDL_Rect& _camara)
{
	GameActor::render(_camara);
}

void GamePawn::update(const unsigned int delta) {
	GameActor::update(delta);
}

//void GamePawn::deleteGameObjet()
//{
//	GameActor::deleteGameObject();
//}
