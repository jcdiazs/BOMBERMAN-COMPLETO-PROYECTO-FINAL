#include "GameActor.h"

TilesGraph* GameActor::tilesGraph = nullptr;

GameActor::GameActor() :GameObject() , Sprite(nullptr, nullptr){
	solido = true;
	indestructible = false;
	visible = true;
	movil = false;
	enMovimiento = false;
	aereo = false;
	terrestre = true;
	subterraneo = false;

	velocidad = 1;
	energia = 100;
	vidas = 5;

	tileActual = nullptr;
	tileSiguiente = nullptr;
	direccionActual = MOVE_DIRECTION_NONE;
	direccionSiguiente = MOVE_DIRECTION_NONE;
}

GameActor::GameActor(std::shared_ptr<SDL_Texture> _textura, SDL_Renderer* _renderer, Tile* _tileActual) :GameObject(), Sprite(_textura, _renderer) {
	solido = true;
	indestructible = false;
	visible = true;
	movil = false;
	enMovimiento = false;
	aereo = false;
	terrestre = true;
	subterraneo = false;

	velocidad = 1;
	energia = 100;
	vidas = 3;

	tileActual = _tileActual;
	tileSiguiente = nullptr;
	direccionActual = MOVE_DIRECTION_NONE;
	direccionSiguiente = MOVE_DIRECTION_NONE;
}


void GameActor::render(SDL_Rect& _camera) {
	if (visible) {
		Sprite::render(_camera);
	}
}

void GameActor::update(const unsigned int delta)
{
	Sprite::update(delta);

	animacion->play();

}


bool GameActor::tratarDeMover(MoveDirection _direccionNueva) {

	Tile* tileDestino = nullptr;

	switch (_direccionNueva)
	{
	case MOVE_DIRECTION_ARRIBA:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX(), tileActual->getPosicionTileY() - 1);
		break;
	case MOVE_DIRECTION_ABAJO:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX(), tileActual->getPosicionTileY() + 1);
		break;
	case MOVE_DIRECTION_IZQUIERDA:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX() - 1, tileActual->getPosicionTileY());
		break;
	case MOVE_DIRECTION_DERECHA:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX() + 1, tileActual->getPosicionTileY());
		break;
	}

	// Si tileDestino es nullptr, no se puede avanzar
	if (tileDestino == nullptr) {
		setTileSiguiente(nullptr);
		return false;
	}

	if (tileDestino->getMuroMetal() != nullptr)
	{
		setTileSiguiente(nullptr);
		return false;
	}

	if (tileDestino->getMuroCeramica() != nullptr)
	{
		setTileSiguiente(nullptr);
		return false;
	}

	setTileSiguiente(tileDestino);
	return true;
}