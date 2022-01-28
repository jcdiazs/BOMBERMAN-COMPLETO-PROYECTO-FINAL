#include "Bomberman.h"

Bomberman::Bomberman(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual):GamePawn(_texture, _renderer, _tileActual)
{

	tileActual = _tileActual;
	tileSiguiente = nullptr;

	if (tileActual != nullptr) {
		tileActual->setBomberman(this);

		setPosition(tileActual->getPosicionTileX() * Tile::anchoTile, tileActual->getPosicionTileY() * Tile::altoTile);
		setSize(Tile::anchoTile, Tile::altoTile);

	}
	else {
		setPosition(0, 0);
		setSize(0, 0);
	}

	velocidad = 3;
	movil = true;
	enMovimiento = false;
	direccionActual = MOVE_DIRECTION_NONE;
	direccionSiguiente = MOVE_DIRECTION_NONE;


	animacion = std::make_shared<Animation>();
	animacion->addAnimationEntity(AnimationEntity(0, 0, Tile::anchoTile, Tile::altoTile));
	animacion->addAnimationEntity(AnimationEntity(Tile::anchoTile * 1, 0, Tile::anchoTile, Tile::altoTile));
	animacion->addAnimationEntity(AnimationEntity(Tile::anchoTile * 2, 0, Tile::anchoTile, Tile::altoTile));
	animacion->setSprite(this);
	addAnimation(animacion);
	animacion->play();
}

void Bomberman::render(SDL_Rect& _camara) {
	GamePawn::render(_camara);
}

void Bomberman::update(const unsigned int _delta) {
	direccionSiguiente = MOVE_DIRECTION_NONE;

	if (keyboardInput->IsKeyOn(botonAbajo)) {
		direccionSiguiente = MOVE_DIRECTION_ABAJO;
	}
	else if (keyboardInput->IsKeyOn(botonArriba)) {
		direccionSiguiente = MOVE_DIRECTION_ARRIBA;
	}
	else if (keyboardInput->IsKeyOn(botonDerecha)) {
		direccionSiguiente = MOVE_DIRECTION_DERECHA;
	}
	else if (keyboardInput->IsKeyOn(botonIzquierda)) {
		direccionSiguiente = MOVE_DIRECTION_IZQUIERDA;
	}

	
	if (direccionSiguiente != direccionActual && tratarDeMover(direccionSiguiente)){
		direccionActual = direccionSiguiente;
		enMovimiento = true;
	}
	else if(direccionSiguiente != MOVE_DIRECTION_NONE)
		tratarDeMover(direccionActual);

		if (tileSiguiente == nullptr)
			enMovimiento = false;
		else{
			enMovimiento = true;
			//if (tileSiguiente != nullptr) {
			switch (direccionActual) { 
			case MOVE_DIRECTION_ARRIBA:
				setPosition(getPositionX(), std::max(getPositionY() - velocidad, tileSiguiente->getPosicionTileY() * Tile::altoTile));
				break;
			case MOVE_DIRECTION_ABAJO:
				setPosition(getPositionX(), std::min(getPositionY() + velocidad, tileSiguiente->getPosicionTileY() * Tile::altoTile));
				break;
			case MOVE_DIRECTION_IZQUIERDA:
				setPosition(std::max(getPositionX() - velocidad, tileSiguiente->getPosicionTileX() * Tile::anchoTile), getPositionY());
				break;
			case MOVE_DIRECTION_DERECHA:
				setPosition(std::min(getPositionX() + velocidad, tileSiguiente->getPosicionTileX() * Tile::anchoTile), getPositionY());
				break;
			}

			// Asignacion de coliciones
			//
			//

			// Cambio de direccion

			if ((direccionActual == MOVE_DIRECTION_ABAJO || direccionActual == MOVE_DIRECTION_ARRIBA) && getPositionY() == tileSiguiente->getPosicionTileY() * Tile::altoTile)
				setTileActual(tileSiguiente);

			if ((direccionActual == MOVE_DIRECTION_IZQUIERDA || direccionActual == MOVE_DIRECTION_DERECHA) && getPositionX() == tileSiguiente->getPosicionTileX() * Tile::anchoTile)
				setTileActual(tileSiguiente);
		}

	GamePawn::update(_delta);
}


void Bomberman::setTileActual(Tile* _tileNuevo)
{
	if (tileActual != nullptr){
		tileActual->setBomberman(nullptr);
	}

	tileActual = _tileNuevo;

	if (tileActual != nullptr) {
		tileActual->setBomberman(this);

		setPosition(tileActual->getPosicionTileX() * Tile::anchoTile, tileActual->getPosicionTileY() * Tile::altoTile);
	}
}
