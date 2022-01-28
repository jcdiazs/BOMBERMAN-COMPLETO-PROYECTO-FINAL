#include "DecoratorWall.h"

void DecoratorWall::render(const SDL_Rect& _camera)
{
	wall->render(_camera);
}
