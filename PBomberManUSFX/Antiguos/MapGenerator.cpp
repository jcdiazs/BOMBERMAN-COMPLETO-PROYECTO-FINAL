#include "MapGenerator.h"
#include "Texture.h"

MapGenerator::MapGenerator()
{
	anchoPantalla = 0;
	altoPantalla = 0;
	renderer = nullptr;
}

MapGenerator::MapGenerator(SDL_Renderer* _renderer, int _anchoPantalla, int _altoPantalla, TilesGraph* _tilesGraph):
	anchoPantalla(_anchoPantalla),
	altoPantalla(_altoPantalla),
	renderer(_renderer),
	tilesGraph(_tilesGraph)
{
	
}

bool MapGenerator::crearObjetosJuego(string _path)
{
	// Crea un flujo de archivo
	fstream file;

	// Abrir el archivo
	file.open(_path.c_str(), ios::in);

	if (file.is_open() == false) {
		std::cout << "No se pudo abrir el archivo de mapa" << std::endl;
		return false;
	}

	string line;
	
	Texture* texturaBomberman;
	texturaBomberman = new Texture();
	Texture* texturaBomberwoman;
	texturaBomberwoman = new Texture();
	Texture* texturaMuroMetal;
	texturaMuroMetal = new Texture();
	Texture* texturaMuroCeramica;
	texturaMuroCeramica = new Texture();
	Texture* texturaSueloCesped;
	texturaSueloCesped = new Texture();
	
	Texture::renderer = renderer;

	texturaBomberman->loadFromImage("resources/bomberman.jpg");
	texturaBomberwoman->loadFromImage("resources/bomberman.jpg");
	texturaMuroCeramica->loadFromImage("resources/muro_ceramica.jpg");
	texturaMuroMetal->loadFromImage("resources/muro_metal.jpg");
	texturaSueloCesped->loadFromImage("resources/suelo_cesped.jpg");
	
	int x = 0;
	int y = 0;
	int bombermanPosicionX = -1;
	int bombermanPosicionY = -1;
	int bomberwomanPosicionX = -1;
	int bomberwomanPosicionY = -1;

	while (getline(file, line)) {
		vector<char> chars(line.begin(), line.end());
		x = 0;

		for (int i = 0; i < chars.size(); i++) {
			if (chars[i] != ' ') {
				GameObject* objetoNuevo = nullptr;
				Tile* tileNuevo = tilesGraph->getTileEn(x, y);
				switch (chars[i]) {
				case '0':
					//objetoNuevo = new SueloCesped(texturaSueloCesped, tileNuevo);
					objetoNuevo = new SueloCesped((std::shared_ptr<SDL_Texture>)texturaSueloCesped->getTexturaSDL(), renderer, tileNuevo);
					if (x > bombermanPosicionX && bombermanPosicionX == -1) {
						bombermanPosicionX = x;
						bombermanPosicionY = y;
					}

					if (x > bomberwomanPosicionX || y > bomberwomanPosicionY) {
						bomberwomanPosicionX = x;
						bomberwomanPosicionY = y;
					}

					//pilaObjetosJuegoMurosMetal.Insertar((GameActor*)objetoNuevo);

					break;
				case '1':
					//objetoNuevo = new MuroCeramica(texturaMuroMetal, tileNuevo);
					objetoNuevo = new MuroCeramica((std::shared_ptr<SDL_Texture>)texturaMuroCeramica->getTexturaSDL(), renderer, tileNuevo);
					break;
					/*case 'B':
						objetoNuevo = new Bomberman(texturaBomberman, tileNuevo);
						break;*/
				case '2':
					//objetoNuevo = new MuroMetal(texturaMuroCeramica, tileNuevo);
					objetoNuevo = new MuroMetal((std::shared_ptr<SDL_Texture>)texturaMuroMetal->getTexturaSDL(), renderer, tileNuevo);
					break;
				}

				if (objetoNuevo != nullptr) {

					((Sprite*)objetoNuevo)->setPosition(x * Tile::anchoTile, y * Tile::altoTile);
					((Sprite*)objetoNuevo)->setSize(Tile::anchoTile, Tile::altoTile);
					((Sprite*)objetoNuevo)->setClip(Tile::anchoTile, Tile::altoTile, x * Tile::anchoTile, y * Tile::altoTile);
			
					vectorObjectosJuego.push_back(objetoNuevo);
					x++;
				}
			}
		}
		y++;
	}

	GameObject* objetoBomberman = nullptr;
	Tile* tileNuevo = tilesGraph->getTileEn(bombermanPosicionX, bombermanPosicionY);
	//objetoBomberman = new Bomberman(texturaBomberman, tileNuevo);
	objetoBomberman = new Bomberman((std::shared_ptr<SDL_Texture>)texturaBomberman->getTexturaSDL(), renderer, tileNuevo);
	if (objetoBomberman != nullptr) {
		((Sprite*)objetoBomberman)->setPosition(bombermanPosicionX * Tile::anchoTile, bombermanPosicionY * Tile::altoTile);
		((Sprite*)objetoBomberman)->setSize(Tile::anchoTile, Tile::altoTile);
		((Sprite*)objetoBomberman)->setClip(Tile::anchoTile, Tile::altoTile, bombermanPosicionX * Tile::anchoTile, bombermanPosicionY * Tile::altoTile);

		vectorObjectosJuego.push_back(objetoBomberman);
	}


	//GameObject* objetoBomberwoman = nullptr;
	//tileNuevo = tilesGraph->getTileEn(bomberwomanPosicionX, bomberwomanPosicionY);
	//objetoBomberwoman = new Bomberman(texturaBomberwoman, tileNuevo);
	//if (objetoBomberwoman != nullptr) {
	//	((GameActor*)objetoBomberwoman)->setPosicionX(bomberwomanPosicionX * 34);
	//	((GameActor*)objetoBomberwoman)->setPosicionY(bomberwomanPosicionY * 34);
	//	((GamePawn*)objetoBomberwoman)->setBotomBomba(SDLK_o);
	//	((GamePawn*)objetoBomberwoman)->setBotomArriba(SDLK_w);
	//	((GamePawn*)objetoBomberwoman)->setBotomAbajo(SDLK_s);
	//	((GamePawn*)objetoBomberwoman)->setBotomIzquierda(SDLK_a);
	//	((GamePawn*)objetoBomberwoman)->setBotomDerecha(SDLK_d);

	//	vectorObjectosJuego.push_back(objetoBomberwoman);
	//}


	return false;
}

void MapGenerator::transferirObjetosJuego(vector<GameObject*>& _vectorObjetosJuegoDestino)
{
	//_vectorObjetosJuegoDestino = vectorObjectosJuego;
	
	for (int i = 0; i < vectorObjectosJuego.size(); i++) {
		_vectorObjetosJuegoDestino.push_back(vectorObjectosJuego[i]);
	}
}
