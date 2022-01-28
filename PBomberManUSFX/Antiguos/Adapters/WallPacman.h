#pragma once
#include <SDL.h>


#include "../Adapters/GameObjectPacman.h"
#include "../Adapters/Texture.h"
#include "../Adapters/TilesGraph.h"

enum WorldDirections {
	DIR_N = 1 << 0,
	DIR_E = 1 << 1,
	DIR_S = 1 << 2,
	DIR_W = 1 << 3
};

class WallPacman : public GameObjectPacman
{
public:
	static TilesGraph* tilesGraph;

	// Prefixed width and height of a WallPacman
	static const int Width = 25;
	static const int Height = 25;

	// Creates connection clips
	static void CreateClips();

	// WallPacman();

	WallPacman(Tile* tile, Texture* texture);
	~WallPacman();

	// Loads texture and sets up animation clips
	// bool LoadMedia();

	// Sets the tile of the WallPacman
	void SetTile(Tile* newTile);

	// Updates the texture of the WallPacman to match connections
	void UpdateConnections();

	// Handles key presses
	// void HandleEvents(SDL_Event* event);

	// Updates the posititon and check collision
	// void Update();

	// Mark the object to be deleted
	void Delete();

	// Renders the WallPacman
	void Render();

	// Releases texture memory
	//void Free();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns WallPacman's tile
	Tile* GetTile();

	virtual void render(const SDL_Rect& camera) {};
	virtual void update(const unsigned int delta) {};
	virtual void handleEvent(SDL_Event* _event) {};

private:
	// Checks if the tile is valid and if there's a WallPacman in it
	bool CheckForWall(Tile* tile);

	Texture* wallTexture;
	int connections;
	static SDL_Rect textureClips[16];

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

