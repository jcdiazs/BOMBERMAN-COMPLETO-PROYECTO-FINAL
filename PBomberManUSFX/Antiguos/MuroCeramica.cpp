#include "MuroCeramica.h"

MuroCeramica::MuroCeramica(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual) :GameActor(_texture, _renderer, _tileActual)
{
	tileActual = _tileActual;

	if (tileActual != nullptr) {
		tileActual->setMuroCeramica(this);
		setPosition(tileActual->getPosicionTileX() * Tile::anchoTile, tileActual->getPosicionTileY() * Tile::altoTile);
		setSize(Tile::anchoTile, Tile::altoTile);
	}
	else {
		setPosition(0, 0);
		setSize(0, 0);
	}

	animacion = std::make_shared<Animation>();
	animacion->addAnimationEntity(AnimationEntity(0, 0, getWidth(), getHeight()));
	//animacion->addAnimationEntity(AnimationEntity(ancho * 1, 0, ancho, alto));
	//animacion->addAnimationEntity(AnimationEntity(ancho * 2, 0, ancho, alto));
	//animacion->addAnimationEntity(AnimationEntity(ancho * 3, 0, ancho, alto));
	//animacion->addAnimationEntity(AnimationEntity(ancho * 4, 0, ancho, alto));
	//animacion->addAnimationEntity(AnimationEntity(ancho * 5, 0, ancho, alto));
	//animacion->addAnimationEntity(AnimationEntity(ancho * 6, 0, ancho, alto));
	//animacion->addAnimationEntity(AnimationEntity(ancho * 7, 0, ancho, alto));
	animacion->setSprite(this);
	addAnimation(animacion);

	animacion->play();
}

void MuroCeramica::setTileActual(Tile* _tileNuevo)
{
	if (tileActual != nullptr) {
		tileActual->setMuroCeramica(nullptr);
	}

	tileActual = _tileNuevo;

	if (tileActual != nullptr) {
		tileActual->setMuroCeramica(this);

		setPosition(tileActual->getPosicionTileX() * Tile::anchoTile, tileActual->getPosicionTileY() * Tile::altoTile);
		setSize(Tile::anchoTile, Tile::altoTile);
	}
	else {
		setPosition(0, 0);
		setSize(0, 0);
	}
}
