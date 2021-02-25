#include "texture.h"

texture::texture()
{
	texture_ = NULL;
	width = 0;
	height = 0;
	pos_x = 0;
	pos_y = 0;
}

//loading texture from file
void texture::load_from_file(std::string file, SDL_Renderer* renderer)
{
	//free memory
	free();

	//loading picture and removing background
	SDL_Surface* surface = IMG_Load(file.c_str());
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;

	set_blend_mode(SDL_BLENDMODE_BLEND);

	SDL_FreeSurface(surface);
}

//loading texture from text
void texture::load_from_text(std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color text_color)
{
	//free memory
	free();

	//loading picture and removing background
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;

	SDL_FreeSurface(surface);
}

//free memory
void texture::free()
{
	//якщо текстура не порожня то звільняємо пам'ять
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}

//change picture parameters
void texture::set_blend_mode(SDL_BlendMode mode)
{
	SDL_SetTextureBlendMode(texture_, mode);
}

//image randering
void texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* sprite_part, SDL_Rect* renderer_squad,double angle)
{
	bool allocated_memory = false;

	if (renderer_squad == NULL)
	{
		renderer_squad = new SDL_Rect;
		allocated_memory = true;
		renderer_squad->x = x;
		renderer_squad->y = y;
		renderer_squad->w = this->width;
		renderer_squad->h = this->height;
	}

	if (sprite_part != NULL)
	{
		renderer_squad->w = sprite_part->w;
		renderer_squad->h = sprite_part->h;
	}

	//change image`s position on screen
	pos_y = y;
	pos_x = x;

	//rendering
	SDL_RenderCopyEx(renderer, texture_, sprite_part, renderer_squad, angle, NULL, SDL_FLIP_NONE);

	//if was allocated memory then freeing this
	if (allocated_memory)
		delete renderer_squad;
}

//geting current position
int texture::get_position_x()
{
	return pos_x;
}

int texture::get_position_y()
{
	return pos_y;
}

//getters for image`s sizes
int texture::get_height()
{
	return height;
}

int texture::get_width()
{
	return width;
}

//destruktor
texture::~texture()
{
	free();
}