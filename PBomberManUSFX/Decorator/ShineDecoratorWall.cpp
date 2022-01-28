#include "ShineDecoratorWall.h"

void ShineDecoratorWall::render(const SDL_Rect& _camera)
{
	DecoratorWall::render(_camera);
	std::cout << "dentro de ShineDecoratorWall" << std::endl;
}