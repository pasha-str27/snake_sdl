#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

//клас текстури
class texture
{
	SDL_Texture* texture_;//сама текстура
	int width;//розміри
	int height;
	int pos_x;//поточна позиція на екрані
	int pos_y;
	SDL_Rect renderer_square;
public:
	//конструктор
	texture();

	//завантаження текстури з файлу
	void load_from_file(std::string file, SDL_Renderer* renderer);

	SDL_Rect get_renderer_square();

	//завантаження текстури з тексту
	void load_from_text(std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color text_color);

	//звільнення пам'яті з-під текстури
	void free();

	//зміна параметрів картинки
	void set_blend_mode(SDL_BlendMode mode);

	//вивід на екран картинки
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* sprite_part=NULL, SDL_Rect* renderer_squad = NULL, double angle = 0);

	//отримання поточних позицій спрайта
	int get_position_x();

	int get_position_y();

	//геттери для розміру текстури
	int get_height();

	int get_width();

	//деструктор
	~texture();
};

