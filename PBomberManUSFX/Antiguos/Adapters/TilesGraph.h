#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "Tile.h"
using namespace std;

class TilesGraph
{
private:

	vector<Tile*> vTilesGraph;
	int getIndice(int _x, int _y);
public:
	static int anchoPantalla;
	static int altoPantalla;
	static int anchoTilesGraph;
	static int altoTilesGraph;

	// Contructores y destructor
	TilesGraph();
	TilesGraph(int _anchoTilesGraph, int _altoTilesGraph, int _anchoPantalla, int _altoPantalla);
	~TilesGraph();

	// Funciones especificas
	Tile* getTileEn(int _x, int _y);

	array<Tile*, 4> get4Vecinos(Tile* _tile);
	array<Tile*, 8> get8Vecinos(Tile* _tile);

	Bomberman* getBomberman();
};

