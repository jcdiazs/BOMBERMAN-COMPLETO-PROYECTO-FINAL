#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "Tile.h"

using namespace std;
//class Pacmam;

class TileGraph
{
public:
	TileGraph();
	TileGraph(int w, int h);
	~TileGraph();

	// (Re)Creates all tiles
	void Setup(int w, int h);

	// Returns tile at given position
	Tile* GetTileAt(int x, int y);

	// Returns neighbours of given tiles
	// 0 - N
	// 1 - E
	// 2 - S
	// 3 - W
	// 4 - NE
	// 5 - SE
	// 6 - SW
	// 7 - NW
	std::array<Tile*, 4> GetNeighbours(Tile* tile);
	std::array<Tile*, 8> GetNeighboursDiag(Tile* tile);

	//Pacman* GetPacman();

private:
	Tile* tiles;
	vector<Tile*> tilesGraph;
	static int widthTileGraph;
	static int heightTileGraph;

	int GetIndex(int x, int h);
};

