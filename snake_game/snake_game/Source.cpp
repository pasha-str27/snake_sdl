#include "texture.h"
#include "score_file_controller.h"
#include "blocks_generator.h"
#include "detect_collisions.h"
#include "Snake.h"
#include <ctime>
#include <string>


#define screen_height 1000
#define screen_width 1580

int main(int arc, char** argv)
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	//створюЇмо зм≥нн≥ дл¤ роботи програми
	SDL_Window* main_window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	SDL_Renderer* main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

	

	texture background;//текстура гравц¤
	background.load_from_file("images/background.png", main_renderer);

	TTF_Font* text_font = TTF_OpenFont("fonts/18545.ttf", 60);
	SDL_Color text_color = { 54,55,28 };

	int current_score = 0;

	texture score;//текстура гравц¤
	texture game_over;

	texture best_score;//текстура гравц¤
	best_score.load_from_text("Best: " + std::to_string(get_best_result()), text_font, main_renderer, text_color);
	score.load_from_text("Score: " + std::to_string(0), text_font, main_renderer, text_color);
	TTF_CloseFont(text_font);
	text_font= TTF_OpenFont("fonts/18545.ttf", 160);
	game_over.load_from_text("Game over!", text_font, main_renderer, text_color);
	TTF_CloseFont(text_font);
	text_font = TTF_OpenFont("fonts/18545.ttf", 60);
	SDL_Rect background_rect = { 20,100,screen_width-40,screen_height-120 };
	texture tip;
	tip.load_from_text("press SPACE to start new game", text_font, main_renderer, text_color);
	bool is_finished_game = false;

	int step = 44;
	int width = (background_rect.w - background_rect.x) / step;
	int height = (background_rect.h - background_rect.y) / step;


	Snake snake(main_renderer, 44);

	//позиц≥¤ зображенн¤ куди маЇ рухатис¤ зображенн¤
	int new_hero_pos_x = screen_width / 2 + (screen_width / 2) % step;
	int new_hero_pos_y = screen_height / 2 + (screen_height / 2) % step;

	float angle = 0;

	texture block;
	block.load_from_file("images/body_part.png", main_renderer);

	blocks_generator blocks_gen;

	std::vector<SDL_Rect> taken_pos;

	SDL_Rect player_pos = { new_hero_pos_x ,new_hero_pos_y , step ,step };
	SDL_Rect next_player_pos = { new_hero_pos_x+step,new_hero_pos_y,step,step };

	taken_pos.push_back(player_pos);

	SDL_Rect block_pos = blocks_gen.generate_new_position(background_rect, step,width,height, taken_pos);

	detect_collisions controll_collisions;

	//крок на поточному кадр≥ 
	int step_x = step;
	int step_y = 0;

	int scree_freequency = 800;

	int frame_count = 0;
	
	bool collected_coin = false;

	SDL_Rect temp = { background_rect.x+20,background_rect.y+20,background_rect.w - 40,background_rect.h-40 };


	//доки не закриЇмо програму
	SDL_Event events;
	bool exit = false;
	while (!exit)
	{
		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_QUIT)
			{
				exit = true;
				save_result(current_score);
				break;
			}

			//¤кщо натиснуто кнопку, зм≥нюЇмо крок руху геро¤ залежно в≥д натиснутоњ кнопки
			if ((events.type == SDL_KEYDOWN || events.type == SDL_KEYUP) && events.key.repeat == 0)
			{
				if (is_finished_game&& events.key.keysym.sym== SDLK_SPACE)
				{
					save_result(current_score);
					current_score = 0;
					snake.reset();
					score.load_from_text("Score: " + std::to_string(current_score), text_font, main_renderer, text_color);
					best_score.load_from_text("Best: " + std::to_string(get_best_result()), text_font, main_renderer, text_color);
					new_hero_pos_x = screen_width / 2 + (screen_width / 2) % step;
					new_hero_pos_y = screen_height / 2 + (screen_height / 2) % step;
					scree_freequency = 800;
					frame_count = 0;
					is_finished_game = false;
					taken_pos.clear();
					taken_pos.push_back(player_pos);
					break;
				}

				switch (events.key.keysym.sym)
				{

				case SDLK_UP://рух вгору
					if (angle == 90)
						break;
					step_y = -step;
					step_x = 0;
					angle = -90;
					break;
				case SDLK_DOWN://рух вниз
					if (angle == -90)
						break;
					step_y = step;
					step_x = 0;
					angle = 90;
					break;
				case SDLK_LEFT://рух вл≥во
					if (angle == 0)
						break;
					step_x = -step;
					step_y = 0;
					angle = 180;
					break;
				case SDLK_RIGHT://рух вправо
					if (angle == 180)
						break;
					step_x = step;
					step_y = 0;
					angle = 0;
					break;
				default:
					break;
				}
			}
		}

		++frame_count;

		//виводимо на екран текстури доки не вийдемо з програми
		SDL_SetRenderDrawColor(main_renderer, 177, 205, 141, 255);
		SDL_RenderClear(main_renderer);

		//¤кщо текстура гравц¤ не виходить за меж≥ екрана, зм≥нюЇмо позиц≥ю текструри
		if (frame_count == scree_freequency && !is_finished_game &&
			(new_hero_pos_x + step_x >= background_rect.x && new_hero_pos_x + step_x + step <= background_rect.w &&
				new_hero_pos_y + step_y >= background_rect.y && new_hero_pos_y + step_y - step <= background_rect.h))
		{
			new_hero_pos_x += step_x;
			new_hero_pos_y += step_y;
		}
		else
			if(frame_count == scree_freequency)
				is_finished_game = true;


		background.render(main_renderer, 10, 100, NULL, &temp);

		block.render(main_renderer, block_pos.x, block_pos.y, NULL, &block_pos);


		for (SDL_Rect a : snake.get_positions_boby_parts())
			block.render(main_renderer, a.x, a.y, NULL, &a);

		if (!is_finished_game &&frame_count == scree_freequency)
		{
			frame_count = 0;
			snake.change_positions();
			taken_pos.clear();
			taken_pos.push_back(player_pos);
			for(SDL_Rect rect:snake.get_positions_boby_parts())
				taken_pos.push_back(rect);
			collected_coin = false;
		}

		player_pos = { new_hero_pos_x ,new_hero_pos_y , step ,step };


		snake.get_snake_head().render(main_renderer, new_hero_pos_x, new_hero_pos_y, NULL, &player_pos, angle);
		if (controll_collisions.collision_with_block(block_pos, player_pos))
		{
			scree_freequency -= 5;
			++current_score;
			collected_coin = true;
			block_pos = blocks_gen.generate_new_position(background_rect, step, width, height, taken_pos);
			score.load_from_text("Score: " + std::to_string(current_score), text_font, main_renderer, text_color);
			snake.add_new_body_part();
		}

		best_score.render(main_renderer, 20, 20);

		score.render(main_renderer, screen_width / 2 + 430, 20);

		if (!collected_coin)
		{
			for (SDL_Rect rect : snake.get_positions_boby_parts())
			{
				if (controll_collisions.collision_with_block(rect, player_pos))
				{
					is_finished_game = true;
					break;
				}
			}
		}


		if (is_finished_game)
		{
			game_over.render(main_renderer, screen_width / 2-450, screen_height / 2-200);
			tip.render(main_renderer, screen_width / 2 - 450, screen_height / 2 + 300);
		}


		SDL_RenderPresent(main_renderer);
	}

	//зв≥льненн¤ пам'¤т≥
	block.free();
	background.free();
	score.free();
	best_score.free();
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	main_renderer = NULL;
	main_window = NULL;
	SDL_Quit();
	IMG_Quit();
	TTF_CloseFont(text_font);
	TTF_Quit();

	return 0;
}