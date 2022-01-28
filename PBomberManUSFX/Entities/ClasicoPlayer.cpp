#include "ClasicoPlayer.h"

ClasicoPlayer::ClasicoPlayer(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer):Player(_texture, _renderer)
{
	speed = 0.004f;
}
