#pragma once

#include <SDL.h>
#include <vector>
#include "texture.h"

class Snake
{
	texture head;
	std::vector<SDL_Rect>body_parts;
	int block_size;
public:
	Snake(SDL_Renderer* main_renderer,int block_size);
	std::vector<SDL_Rect>get_positions_boby_parts();
	texture& get_snake_head();
	void change_positions();
	void add_new_body_part();
	void reset();
	~Snake();
};

