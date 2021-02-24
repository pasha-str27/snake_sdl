#pragma once

#include <SDL.h>

class detect_collisions
{
public:
	bool collision_with_block(SDL_Rect block, SDL_Rect snake_head);
};

