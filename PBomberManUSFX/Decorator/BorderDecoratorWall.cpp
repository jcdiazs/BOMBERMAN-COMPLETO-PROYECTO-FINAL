#include "BorderDecoratorWall.h"

void BorderDecoratorWall::render(const SDL_Rect& _camera)
{
	DecoratorWall::render(_camera);
	std::cout << "dentro de BorderDecoratorWall" << std::endl;
}
