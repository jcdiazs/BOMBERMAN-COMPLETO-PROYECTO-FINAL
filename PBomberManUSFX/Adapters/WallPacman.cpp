#include "WallPacman.h"

SDL_Rect WallPacman::textureClips[16];

//WallPacman::WallPacman()
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

	textureClips[0] = { 0, 0, 32, 64 };
	textureClips[DIR_N] = { 32, 0, 32, 32 };
	textureClips[DIR_E] = { 64, 0, 32, 32 };
	textureClips[DIR_S] = { 96, 0, 32, 32 };
	textureClips[DIR_W] = { 0, 32, 33, 33 };
	textureClips[DIR_N | DIR_E] = { 32, 32, 32, 32 };
	textureClips[DIR_S | DIR_E] = { 64, 32, 32, 32 };
	textureClips[DIR_S | DIR_W] = { 96, 32, 32, 32 };
	textureClips[DIR_N | DIR_W] = { 0, 64, 32, 32 };
	textureClips[DIR_N | DIR_S] = { 64, 128, 32, 32 };
	textureClips[DIR_E | DIR_W] = { 96, 128, 32, 32 };
	textureClips[DIR_N | DIR_E | DIR_W] = { 32, 64, 32, 32 };
	textureClips[DIR_N | DIR_E | DIR_S] = { 64, 64, 32, 32 };
	textureClips[DIR_E | DIR_S | DIR_W] = { 96, 64, 32, 32 };
	textureClips[DIR_N | DIR_S | DIR_W] = { 0, 96, 32, 32 };
	textureClips[DIR_N | DIR_E | DIR_S | DIR_W] = { 32, 96, 32, 32 };
}

WallPacman::WallPacman(Tile* tile, Texture* texture)
{
	currTile = tile;

	wallTexture = texture;

	if (currTile != nullptr) {
		currTile->SetWall(this);

		position.x = currTile->GetPosition().x * Tile::tileWidth;
		position.y = currTile->GetPosition().y * Tile::tileHeight;
		/*cout << "Aqui" << endl;
		cout << currTile->GetPosition().x << ", " << currTile->GetPosition().y << endl;*/
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Tile::tileWidth;
	collider.h = Tile::tileHeight;

	
	UpdateConnections();
	
	std::array<Tile*, 4> neighbours = tileGraph->GetNeighbours(this->currTile);
	for (int i = 0; i < 4; i++) {
		if (CheckForWall(neighbours[i]))
			neighbours[i]->GetWall()->UpdateConnections();
	}
}

WallPacman::~WallPacman()
{
	Free();
}

void WallPacman::SetTile(Tile* newTile)
{
	if (currTile != nullptr)
		currTile->SetWall(nullptr);

	currTile = newTile;

	if (currTile != nullptr) {
		currTile->SetWall(this);

		position.x = currTile->GetPosition().x * Tile::tileWidth;
		position.y = currTile->GetPosition().y * Tile::tileHeight;
	}
}

void WallPacman::UpdateConnections()
{
	std::array<Tile*, 4> neighbours = tileGraph->GetNeighbours(this->currTile);

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
	// Calling base function
	GameObjectPacman::Delete();

	currTile->SetWall(nullptr);
}

void WallPacman::Render()
{
	wallTexture->Render(position.x, position.y, &textureClips[connections]);
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
	if (tile != nullptr && tile->GetWall() != nullptr)
		return true;

	return false;
}
