#pragma once
#include <iostream>
#include "GamePawn.h"

using namespace std;

class Bomberman : public GamePawn
{
private:

public:
	//Constructor
	Bomberman(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer, Tile* _tileActual);
	
	void setTileActual(Tile* _tileNuevo) override;
	void render(SDL_Rect& _camera);
	void update(const unsigned int _delta);

};

