#include "texture.h"


//конструктор
texture::texture()//
	{
		texture_ = NULL;
		width = 0;
		height = 0;
	}

	//завантаження текстури з файлу
	void texture::load_from_file(std::string file, SDL_Renderer* renderer)
	{
		//звільнення раніше виділеної пам'яті
		free();

		//завантаження картинки та видалення заднього фону
		SDL_Surface* surface = IMG_Load(file.c_str());
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		//присвоєння даних для полів класу
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		width = surface->w;
		height = surface->h;

		//зміна параметрів текстури
		set_blend_mode(SDL_BLENDMODE_BLEND);

		//звільнення пам'яті
		SDL_FreeSurface(surface);
	}

	SDL_Rect texture::get_renderer_square()
	{
		return renderer_square;
	}

	//завантаження текстури з тексту
	void texture::load_from_text(std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color text_color)
	{
		//звільнення раніше виділеної пам'яті
		free();

		//завантаження картинки та видалення заднього фону
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		//присвоєння даних для полів класу
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		width = surface->w;
		height = surface->h;

		//звільнення пам'яті
		SDL_FreeSurface(surface);
	}

	//звільнення пам'яті з-під текстури
	void texture::free()
	{
		//якщо текстура не порожня то звільняємо пам'ять
		if (texture_ != NULL)
		{
			SDL_DestroyTexture(texture_);
			texture_ = NULL;
			width = 0;
			height = 0;
		}
	}

	//зміна параметрів картинки
	void texture::set_blend_mode(SDL_BlendMode mode)
	{
		SDL_SetTextureBlendMode(texture_, mode);
	}

	//вивід на екран картинки
	void texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* sprite_part, SDL_Rect* renderer_squad,double angle)
	{
		bool allocated_memory = false;
		//формуємо квадрат що відповідає розташуванню текстури на екрані
		if (renderer_squad == NULL)
		{
			renderer_squad = new SDL_Rect;
			allocated_memory = true;
			renderer_squad->x = x;
			renderer_squad->y = y;
			renderer_squad->w = this->width;
			renderer_squad->h = this->height;
			renderer_square = { renderer_squad->x,renderer_squad->y,renderer_squad->w,renderer_squad->h };
		}

		if (sprite_part != NULL)
		{
			renderer_squad->w = sprite_part->w;
			renderer_squad->h = sprite_part->h;
		}
		//зміна позиції зображення
		pos_y = y;
		pos_x = x;
		//та вивід на екран
		SDL_RenderCopyEx(renderer, texture_, sprite_part, renderer_squad, angle, NULL, SDL_FLIP_NONE);

		if (allocated_memory)
			delete renderer_squad;
	}

	//отримання поточних позицій спрайта
	int texture::get_position_x()
	{
		return pos_x;
	}

	int texture::get_position_y()
	{
		return pos_y;
	}

	//геттери для розміру текстури
	int texture::get_height()
	{
		return height;
	}

	int texture::get_width()
	{
		return width;
	}

	//деструктор
	texture::~texture()
	{
		free();//очищуємо пам'ять

	texture_ = NULL;
	width = 0;
	height = 0;
}