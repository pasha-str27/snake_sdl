#pragma once
#include <SDL.h>
#include <vector>

//generator for blocks
class blocks_generator
{
public:
	//generating random position for coin
	SDL_Rect generate_new_position(SDL_Rect border, int block_size, int field_width, int field_height, std::vector<SDL_Rect> taken_position);
	
	//checking taken position or no
	bool is_taken_pos(int pos_x, int pos_y, std::vector<SDL_Rect> taken_position);
};