#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


class Texture
{
private:
	SDL_Texture* texturaSDL;
	int ancho;
	int alto;
public:
	static SDL_Renderer* renderer;

public:
	Texture();
	Texture(SDL_Renderer* _renderer);

	~Texture();

	void free();

	// Metodos accesores
	SDL_Texture* getTexturaSDL() { return texturaSDL; }
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	SDL_Renderer* getRenderer() { return renderer; }

	void setTexturaSDL(SDL_Texture* _texturaSDL) { texturaSDL = _texturaSDL; }
	void setAncho(int _ancho) { ancho = _ancho; }
	void setAlto(int _alto) { alto = _alto; }
	void setRenderer(SDL_Renderer* _renderer) { renderer = _renderer; }

	// Metodos especificos
	bool loadFromImage(std::string path, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);
	void render(int x, int y, SDL_Rect* clip = nullptr, SDL_Rect* rect = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip renderFlip = SDL_FLIP_NONE);
};

