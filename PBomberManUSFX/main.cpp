#include <string>

#include "SDL.h"

#include "GameManager.h"

int main(int /*argc*/, char** /*argv[]*/)
{
    // init game

     std::cout << "BOMBERMAN USFX" << std::endl;
     std::cout << "Alumno: Diaz Soliz Jhon Carlos" << std::endl;
     std::cout << " Ingenieria en Tecnologias de la Informacion y Seguridad" << std::endl;
     std::cout << "" << std::endl;
     std::cout << "Alumno: Adriana Jasiel Campos Romero" << std::endl;
     std::cout << "Ingenieria en Ciencias de la Computación" << std::endl;
    GameManager* game = nullptr;
    game = GameManager::getInstance(std::string("Bomberman USFX"), 800, 600);
    // game = new GameManager(std::string("Bomberman USFX"), 800, 600);
    // run game loop
    game->execute();

    return 0;
}
