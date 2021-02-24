#pragma once

#include <SDL.h>

//deteckting colisions with blocks
class detect_collisions
{
public:
	bool collision_with_block(SDL_Rect block, SDL_Rect snake_head);
};

