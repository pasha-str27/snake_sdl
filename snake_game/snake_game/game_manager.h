#pragma once
#include <SDL.h>
#include <string>
#include "texture.h"
#include "score_file_controller.h"
#include "Snake.h"
#include "detect_collisions.h"
#include "blocks_generator.h"

class game_manager
{
	int screen_height;
	int screen_width;

	SDL_Window* main_window;
	SDL_Renderer* main_renderer;
	texture background;
	texture score;
	texture game_over;
	texture best_score;
	texture tip;
	texture block;
	TTF_Font* text_font;
	SDL_Color text_color;

	Snake snake;

	detect_collisions controll_collisions;//processing collisions with blocks

	blocks_generator blocks_gen;//coins generator

	SDL_Rect background_rect;
	//rect with game field
	SDL_Rect temp;

	std::vector<SDL_Rect> taken_pos;//taken positions
	bool is_finished_game;//lost player or no
	int step;//size of coin/snake`s part body
	int width;//numbers of columns on screen
	int height;//numbers of rows on screen

	//snake`s position on start game
	int new_hero_pos_x ;
	int new_hero_pos_y ;

	//angle of rotation for snake`s head
	float angle;

	SDL_Rect player_pos;//screen rect where will snake`s head
	int current_score;
	int scree_freequency; //each scree_freequency frames change posision of snake
	int frame_count;//frame counter

	int step_x = step;//direction for snake moving
	int step_y = 0;
public:
	game_manager(int screen_height,int screen_width);
	void init();//init objects
	void reset();//game reset
	void play();//game logic
	void exit();//memory free
	bool detect_events();//events controlling
	void render(SDL_Rect &block_pos, bool &collected_coin);//rendering
};

