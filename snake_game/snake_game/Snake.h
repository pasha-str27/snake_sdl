#pragma once

#include <SDL.h>
#include <vector>
#include "texture.h"

class Snake
{
	texture head;//snake`s head
	std::vector<SDL_Rect>body_parts;//snake`s boby parts
	int block_size;//size of block
public:
	Snake(SDL_Renderer* main_renderer,int block_size);//konstruktor
	std::vector<SDL_Rect>get_positions_boby_parts();//geting  positions of body parts
	texture& get_snake_head();//geting  head
	void change_positions();//changing positions
	void add_new_body_part();//adding new body part
	void reset();//remove all body parts
	~Snake();//destruktor
};

