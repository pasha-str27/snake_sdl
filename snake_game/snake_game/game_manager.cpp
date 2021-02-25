#include "game_manager.h"

//init objects
void game_manager::init()
{
	main_window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

	text_font = TTF_OpenFont("fonts/18545.ttf", 60);
	text_color = { 54,55,28 };

	block.load_from_file("images/body_part.png", main_renderer);
	background.load_from_file("images/background.png", main_renderer);
	best_score.load_from_text("Best: " + std::to_string(get_best_result()), text_font, main_renderer, text_color);
	score.load_from_text("Score: " + std::to_string(0), text_font, main_renderer, text_color);
	TTF_CloseFont(text_font);
	text_font = TTF_OpenFont("fonts/18545.ttf", 160);
	game_over.load_from_text("Game over!", text_font, main_renderer, text_color);
	TTF_CloseFont(text_font);
	text_font = TTF_OpenFont("fonts/18545.ttf", 60);
	tip.load_from_text("press SPACE to start new game", text_font, main_renderer, text_color);

	snake.init(main_renderer,44);

	is_finished_game = false;
}

void game_manager::play()
{
	int current_score = 0;

	background_rect = { 20,100,screen_width - 40,screen_height - 120 };

	step = 44;//size of coin/snake`s part body
	width = (background_rect.w - background_rect.x) / step;//numbers of columns on screen
	height = (background_rect.h - background_rect.y) / step;//numbers of rows on screen

	//snake`s position on start game
	new_hero_pos_x = screen_width / 2 + (screen_width / 2) % step;
	new_hero_pos_y = screen_height / 2 + (screen_height / 2) % step;

	//angle of rotation for snake`s head
	angle = 0;

	player_pos = { new_hero_pos_x ,new_hero_pos_y , step ,step };//screen rect where will snake`s head

	taken_pos.push_back(player_pos);

	//generating position for coin
	SDL_Rect block_pos = blocks_gen.generate_new_position(background_rect, step, width, height, taken_pos);

	step_x = step;//direction for snake moving
	step_y = 0;

	scree_freequency = 800; //each scree_freequency frames change posision of snake

	 frame_count = 0;//frame counter

	bool collected_coin = false;//collected coin or no

	//rect with game field
	temp = { background_rect.x + 20,background_rect.y + 20,background_rect.w - 40,background_rect.h - 40 };

	while (true)
	{
		//events` processing
		if (detect_events())
			break;

		//increase frame`s counter
		++frame_count;

		//if snake`s head is on game field then change position for snake`s head
		if (frame_count == scree_freequency && !is_finished_game &&
			(new_hero_pos_x + step_x >= background_rect.x && new_hero_pos_x + step_x + step <= background_rect.w &&
				new_hero_pos_y + step_y >= background_rect.y && new_hero_pos_y + step_y - step <= background_rect.h))
		{
			new_hero_pos_x += step_x;
			new_hero_pos_y += step_y;
		}
		else
			if (frame_count == scree_freequency)
				is_finished_game = true;//else we say that player lost

		//rendering objects
		render(block_pos, collected_coin);
	}
}

game_manager::game_manager(int screen_height, int screen_width)
{
	main_window = NULL;
	main_renderer = NULL;
	text_font = NULL;
	text_color = { 255,255,255 };
	this->screen_height = screen_height;
	this->screen_width = screen_width;
}

void game_manager::reset()
{
	//save result
	save_result(current_score);

	//and reload game
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
}

void game_manager::exit()
{
	block.free();
	background.free();
	score.free();
	best_score.free();
	game_over.free();
	tip.free();
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	TTF_CloseFont(text_font);
}

bool game_manager::detect_events()
{
	SDL_Event events;
	while (SDL_PollEvent(&events) != 0)
	{
		//if we want exit
		if (events.type == SDL_QUIT)
		{
			save_result(current_score);//save result
			return true;
		}

		//if was prassed button
		if ((events.type == SDL_KEYDOWN || events.type == SDL_KEYUP) && events.key.repeat == 0)
		{
			//if it was space
			if (is_finished_game && events.key.keysym.sym == SDLK_SPACE)
			{
				reset();
				break;
			}

			//if it was buttons which give move direction, change direction
			switch (events.key.keysym.sym)
			{
			case SDLK_UP://move up
				if (angle == 90)
					break;
				step_y = -step;
				step_x = 0;
				angle = -90;
				break;
			case SDLK_DOWN://move down
				if (angle == -90)
					break;
				step_y = step;
				step_x = 0;
				angle = 90;
				break;
			case SDLK_LEFT://move left
				if (angle == 0)
					break;
				step_x = -step;
				step_y = 0;
				angle = 180;
				break;
			case SDLK_RIGHT://move right
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
	return false;
}

void game_manager::render(SDL_Rect &block_pos,bool &collected_coin)
{
	SDL_SetRenderDrawColor(main_renderer, 177, 205, 141, 255);
	SDL_RenderClear(main_renderer);

	background.render(main_renderer, 10, 100, NULL, &temp);

	block.render(main_renderer, block_pos.x, block_pos.y, NULL, &block_pos);

	//rendering body parts of snake
	for (SDL_Rect a : snake.get_positions_boby_parts())
		block.render(main_renderer, a.x, a.y, NULL, &a);

	//if player don`t lose and need to move snake`s boby
	if (!is_finished_game && frame_count == scree_freequency)
	{
		frame_count = 0;
		snake.change_positions();
		taken_pos.clear();
		taken_pos.push_back(player_pos);

		for (SDL_Rect rect : snake.get_positions_boby_parts())
			taken_pos.push_back(rect);

		collected_coin = false;
	}

	//rendering snake`s head
	player_pos = { new_hero_pos_x ,new_hero_pos_y , step ,step };
	snake.get_snake_head().render(main_renderer, new_hero_pos_x, new_hero_pos_y, NULL, &player_pos, angle);

	//if player collected the coin
	if (controll_collisions.collision_with_block(block_pos, player_pos))
	{
		//increase current score and add new body part for snake
		scree_freequency -= 5;
		++current_score;
		collected_coin = true;
		block_pos = blocks_gen.generate_new_position(background_rect, step, width, height, taken_pos);
		score.load_from_text("Score: " + std::to_string(current_score), text_font, main_renderer, text_color);
		snake.add_new_body_part();
	}

	//rendering game result
	best_score.render(main_renderer, 20, 20);
	score.render(main_renderer, screen_width / 2 + 430, 20);

	//if was collected coin
	if (!collected_coin)
	{
		//for all snake`s body parts
		for (SDL_Rect rect : snake.get_positions_boby_parts())
		{
			if (controll_collisions.collision_with_block(rect, player_pos))//check whether snake`s head don`t across with body
			{
				is_finished_game = true;
				break;
			}
		}
	}

	//if player lost
	if (is_finished_game)
	{
		//render massege about this
		game_over.render(main_renderer, screen_width / 2 - 450, screen_height / 2 - 200);
		tip.render(main_renderer, screen_width / 2 - 450, screen_height / 2 + 300);
	}

	SDL_RenderPresent(main_renderer);
}
