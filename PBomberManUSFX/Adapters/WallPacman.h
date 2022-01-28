#pragma once

#include "../Adapters/GameObjectPacman.h"
#include "../Adapters/Texture.h"
#include "../Adapters/TileGraph.h"

enum WorldDirections {
	DIR_N = 1 << 0,
	DIR_E = 1 << 1,
	DIR_S = 1 << 2,
	DIR_W = 1 << 3
};

class WallPacman : public GameObjectPacman
{
public:
	//static TileGraph* tileGraph;

	// Prefixed width and height of a wall
	static const int Width = 32;
	static const int Height = 32;

	// Creates connection clips
	static void CreateClips();

	// WallPacman();

	WallPacman(Tile* tile, Texture* texture);
	~WallPacman();

	// Loads texture and sets up animation clips
	// bool LoadMedia();

	// Sets the tile of the wall
	void SetTile(Tile* newTile);

	// Updates the texture of the wall to match connections
	void UpdateConnections();

	// Handles key presses
	// void HandleEvents(SDL_Event* event);

	// Updates the posititon and check collision
	// void Update();

	// Mark the object to be deleted
	void Delete();

	// Renders the wall
	void Render();

	// Releases texture memory
	// void Free();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns wall's tile
	Tile* GetTile();

	void setSDLPosition(int _x, int _y) {
		position.x = _x;
		position.y = _y;
	}
protected:
	Texture* wallTexture;
	

private:
	// Checks if the tile is valid and if there's a wall in it
	bool CheckForWall(Tile* tile);

	int connections;
	static SDL_Rect textureClips[16];

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

