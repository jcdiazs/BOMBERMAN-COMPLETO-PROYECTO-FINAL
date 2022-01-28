#pragma once

#include <SDL.h>

//class Pacman;
class WallPacman;
//class Point;
//class Blinky;

class Tile
{
public:
	static int tileWidth;
	static int tileHeight;

	Tile();
	Tile(int x, int y);

	// Sets pointer to Pacman in the tile
	//void SetPacman(Pacman* pacman);

	// Sets pointer to wall in the tile
	void SetWall(WallPacman* wall);

	// Sets pointer to point in the tile
	//void SetPoint(Point* wall);

	// Sets pointer to Blinky in the tile
	//void SetBlinky(Blinky* blinky);

	// Sets position of the tile
	void SetPos(int x, int y);

	// Returns pointer to Pacman in the tile
	//Pacman* GetPacman();
	
	// Returns pointer to wall in the tile
	WallPacman* GetWall();

	// Returns pointer to wall in the tile
	//Point* GetPoint();

	// Returns pointer to wall in the tile
	//Blinky* GetBlinky();

	// Returns position of the tile
	SDL_Point GetPosition();

private:
	SDL_Point position;
	
	// GameObjects

	//Pacman* pPacman;
	WallPacman* pWall;
	//Point* pPoint;
	//Blinky* pBlinky;
};

