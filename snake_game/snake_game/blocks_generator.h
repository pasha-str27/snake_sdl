#pragma once
#include <SDL.h>
#include <vector>

class blocks_generator
{
public:
	SDL_Rect generate_new_position(SDL_Rect border, int block_size, int field_width, int field_height, std::vector<SDL_Rect> taken_position);
	bool is_taken_pos(int pos_x, int pos_y, std::vector<SDL_Rect> taken_position);
};

