#include "WallPacman.h"

SDL_Rect WallPacman::textureClips[16];

TilesGraph* WallPacman::tilesGraph = nullptr;

//WallPacman::Wall()
//{
//	currTile = nullptr;
//
//	position.x = 0;
//	position.y = 0;
//
//	collider.w = Width;
//	collider.h = Height;
//}

void WallPacman::CreateClips()
{
	// 0000 - standalone
	// 1000 - N
	// 0100 - E
	// 0010 - S
	// 0001 - W

	textureClips[0] = { 0, 0, 25, 25 };
	textureClips[DIR_N] = { 25, 0, 25, 25 };
	textureClips[DIR_E] = { 50, 0, 25, 25 };
	textureClips[DIR_S] = { 75, 0, 25, 25 };
	textureClips[DIR_W] = { 0, 25, 25, 25 };
	textureClips[DIR_N | DIR_E] = { 25, 25, 25, 25 };
	textureClips[DIR_S | DIR_E] = { 50, 25, 25, 25 };
	textureClips[DIR_S | DIR_W] = { 75, 25, 25, 25 };
	textureClips[DIR_N | DIR_W] = { 0, 50, 25, 25 };
	textureClips[DIR_N | DIR_S] = { 50, 100, 25, 25 };
	textureClips[DIR_E | DIR_W] = { 75, 100, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_W] = { 25, 50, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_S] = { 50, 50, 25, 25 };
	textureClips[DIR_E | DIR_S | DIR_W] = { 75, 50, 25, 25 };
	textureClips[DIR_N | DIR_S | DIR_W] = { 0, 75, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_S | DIR_W] = { 25, 75, 25, 25 };
}

WallPacman::WallPacman(Tile* tile, Texture* texture)
{
	currTile = tile;

	wallTexture = texture;

	if (currTile != nullptr) {
		currTile->setWall(this);

		position.x = currTile->getPosicionTileX() * Width;
		position.y = currTile->getPosicionTileY() * Height;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	UpdateConnections();

	std::array<Tile*, 4> neighbours = tilesGraph->get4Vecinos(this->currTile);
	for (int i = 0; i < 4; i++) {
		if (CheckForWall(neighbours[i]))
			neighbours[i]->getWall()->UpdateConnections();
	}
}

WallPacman::~WallPacman()
{
	//Free();
}

void WallPacman::SetTile(Tile* newTile)
{
	if (currTile != nullptr)
		currTile->setWall(nullptr);

	currTile = newTile;

	if (currTile != nullptr) {
		currTile->setWall(this);

		position.x = currTile->getPosicionTileX() * Width;
		position.y = currTile->getPosicionTileY() * Height;
	}
}

void WallPacman::UpdateConnections()
{
	std::array<Tile*, 4> neighbours = tilesGraph->get4Vecinos(this->currTile);

	connections = 0;

	if (CheckForWall(neighbours[0]))
		connections |= DIR_S;
	if (CheckForWall(neighbours[1]))
		connections |= DIR_E;
	if (CheckForWall(neighbours[2]))
		connections |= DIR_N;
	if (CheckForWall(neighbours[3]))
		connections |= DIR_W;
}

void WallPacman::Delete()
{
	//// Calling base function
	GameObjectPacman::Delete();

	currTile->setWall(nullptr);
}

void WallPacman::Render()
{
	wallTexture->render(position.x, position.y, &textureClips[connections]);
}

SDL_Rect WallPacman::GetCollider()
{
	return collider;
}

SDL_Point WallPacman::GetPosition()
{
	return position;
}

Tile* WallPacman::GetTile()
{
	return currTile;
}

bool WallPacman::CheckForWall(Tile* tile)
{
	if (tile != nullptr && tile->getWall() != nullptr)
		return true;

	return false;
}
