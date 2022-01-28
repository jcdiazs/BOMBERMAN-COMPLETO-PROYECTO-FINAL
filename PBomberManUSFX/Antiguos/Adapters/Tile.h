#pragma once
#include <SDL.h>

//
//#include "Bomberman.h"
//#include "MuroCeramica.h"
//#include "MuroMetal.h"
//#include "SueloCesped.h"

class Bomberman;
class MuroCeramica;
class MuroMetal;
class SueloCesped;
class WallPacman;


class Tile
{
private:
	//Bomberman* bomberman;
	//MuroCeramica* muroCeramica;
	//MuroMetal* muroMetal;
	//SueloCesped* sueloCesped;
	WallPacman* wall;

	int posicionTileX;
	int posicionTileY;

public:
	static const int anchoTile = 32;
	static const int altoTile = 32;

	// Constructores y destructores
	Tile();
	Tile(int _posicionTileX, int _posicionTileY);

	// Metodos accesores
	//Bomberman* getBomberman() { return bomberman; }

	//MuroCeramica* getMuroCeramica() { return muroCeramica; }
	//MuroMetal* getMuroMetal() { return muroMetal; }
	//SueloCesped* getSueloCesped() { return sueloCesped; }
	WallPacman* getWall() { return wall; }
	int getPosicionTileX() { return posicionTileX; }
	int getPosicionTileY() { return posicionTileY; }

	//void setBomberman(Bomberman* _bomberman) { bomberman = _bomberman; }
	//void setMuroCeramica(MuroCeramica* _muroCeramica) { muroCeramica = _muroCeramica; }
	//void setMuroMetal(MuroMetal* _muroMetal) { muroMetal = _muroMetal; }
	//void setSueloCesped(SueloCesped* _sueloCesped) { sueloCesped = _sueloCesped; }
	void setWall(WallPacman* _wall) { wall = _wall; }
	void setPosicionTileX(int _posicionTileX) { posicionTileX = _posicionTileX; }
	void setPosicionTileY(int _posicionTileY) { posicionTileY = _posicionTileY; }
};

