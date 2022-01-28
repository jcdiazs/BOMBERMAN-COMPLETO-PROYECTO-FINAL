#include "Tile.h"

int Tile::tileWidth = 32;
int Tile::tileHeight = 32;

Tile::Tile()
{
	position = { 0,0 };

	//pPacman = nullptr;
	pWall = nullptr;
	//pPoint = nullptr;
}

Tile::Tile(int x, int y)
{
	position = { x,y };

	//pPacman = nullptr;
	pWall = nullptr;
	//pPoint = nullptr;
}

void Tile::SetPos(int x, int y)
{
	position.x = x;
	position.y = y;
}

//void Tile::SetPacman(Pacman* pacman)
//{
//	pPacman = pacman;
//}

void Tile::SetWall(WallPacman* wall)
{
	pWall = wall;
}

//void Tile::SetPoint(Point* point)
//{
//	pPoint = point;
//}

//void Tile::SetBlinky(Blinky* blinky)
//{
//	pBlinky = blinky;
//}

//Pacman* Tile::GetPacman()
//{
//	return pPacman;
//}

WallPacman* Tile::GetWall()
{
	return pWall;
}

//Point* Tile::GetPoint()
//{
//	return pPoint;
//}

//Blinky* Tile::GetBlinky()
//{
//	return pBlinky;
//}

SDL_Point Tile::GetPosition()
{
	return position;
}