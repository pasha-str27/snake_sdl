#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class texture
{
	SDL_Texture* texture_;//texture
	int width;//sizes
	int height;
	int pos_x;//current positions on the screen
	int pos_y;
public:
	texture();

	//loading texture from file
	void load_from_file(std::string file, SDL_Renderer* renderer);

	//loading texture from text
	void load_from_text(std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color text_color);

	//free memore
	void free();

	//change picture parameters
	void set_blend_mode(SDL_BlendMode mode);

	//image randering
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* sprite_part=NULL, SDL_Rect* renderer_squad = NULL, double angle = 0);

	//geting current position
	int get_position_x();

	int get_position_y();

	//getters for image`s sizes
	int get_height();

	int get_width();

	//destruktor
	~texture();
};

