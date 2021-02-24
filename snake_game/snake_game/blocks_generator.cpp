#include "blocks_generator.h"

SDL_Rect blocks_generator::generate_new_position(SDL_Rect border,int block_size,int field_width,int field_height,std::vector<SDL_Rect> taken_positions)
{
	int pos_x, pos_y;
	do {
		pos_x = rand() % field_width * block_size+border.x;
		pos_y = rand() % field_height * block_size + border.y;
	} while (is_taken_pos(pos_x, pos_y, taken_positions));
	return { pos_x+20,pos_y+20 ,block_size,block_size };
}

bool blocks_generator::is_taken_pos(int pos_x, int pos_y, std::vector<SDL_Rect> taken_positions)
{
	for (SDL_Rect rect : taken_positions)
		if (pos_x == rect.x && pos_y == rect.y)
			return true;
	return false;
}
