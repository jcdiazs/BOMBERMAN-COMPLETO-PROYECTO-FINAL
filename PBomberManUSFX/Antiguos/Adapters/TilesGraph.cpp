#include "TilesGraph.h"

int TilesGraph::anchoPantalla = 0;
int TilesGraph::altoPantalla = 0;
int TilesGraph::anchoTilesGraph = 0;
int TilesGraph::altoTilesGraph = 0;

TilesGraph::TilesGraph()
{
    anchoPantalla = 0;
    altoPantalla = 0;
    anchoTilesGraph = 0;
    altoTilesGraph = 0;
}

TilesGraph::TilesGraph(int _anchoTilesGraph, int _altoTilesGraph, int _anchoPantalla, int _altoPantalla)
{
    anchoPantalla = _anchoPantalla;
    altoPantalla = _altoPantalla;
    anchoTilesGraph = _anchoTilesGraph;
    altoTilesGraph = _altoTilesGraph;

    for (int y = 0; y < altoTilesGraph; y++) {
        for (int x = 0; x < anchoTilesGraph; x++) {
            vTilesGraph.push_back(new Tile(x, y));
        }
    }

}

TilesGraph::~TilesGraph()
{
    vTilesGraph.clear();
}

int TilesGraph::getIndice(int _x, int _y)
{
    if (_x >= anchoTilesGraph || _y >= altoTilesGraph)
        return -1;
    if (_x < 0 || _y < 0)
        return -1;

    return _x + _y * anchoTilesGraph;
}

Tile* TilesGraph::getTileEn(int _x, int _y)
{
    int indice = getIndice(_x, _y);

    if (indice < 0)
        return nullptr;
    
    return vTilesGraph[indice];
}

array<Tile*, 4> TilesGraph::get4Vecinos(Tile* _tile)
{
    array<Tile*, 4> vecinos;

    int x = _tile->getPosicionTileX();
    int y = _tile->getPosicionTileY();

    vecinos[0] = getTileEn(x, y + 1);
    vecinos[1] = getTileEn(x, y - 1);
    vecinos[2] = getTileEn(x + 1, y);
    vecinos[3] = getTileEn(x - 1, y);

    return vecinos;
}

array<Tile*, 8> TilesGraph::get8Vecinos(Tile* _tile)
{
    array<Tile*, 8> vecinos;

    int x = _tile->getPosicionTileX();
    int y = _tile->getPosicionTileY();

    vecinos[0] = getTileEn(x, y + 1);
    vecinos[1] = getTileEn(x, y - 1);
    vecinos[2] = getTileEn(x + 1, y);
    vecinos[3] = getTileEn(x - 1, y);
    vecinos[4] = getTileEn(x + 1, y + 1);
    vecinos[5] = getTileEn(x - 1, y - 1);
    vecinos[6] = getTileEn(x + 1, y - 1);
    vecinos[7] = getTileEn(x - 1, y + 1);

    return vecinos;
}

Bomberman* TilesGraph::getBomberman()
{
    /*for (int i = 0 : i < tilesGraph.size(); i++) {
        if( tilesGraph[i]->getBomberman() != null){
            return tilesGraph[i]->getBomberman();
        }
    }*/

  /*  for (auto itg = vTilesGraph.begin(); itg != vTilesGraph.end(); ++itg) {
        if ((*itg)->getBomberman() != nullptr) {
            return (*itg)->getBomberman();
        }
    }*/

    return nullptr;
}
