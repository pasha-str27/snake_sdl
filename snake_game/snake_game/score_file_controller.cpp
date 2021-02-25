#pragma once
#include "score_file_controller.h"

//reading best score from file
int get_best_result()
{
	int score = 0;
	SDL_RWops* file = SDL_RWFromFile("result.bin", "r+b");
	if (file == NULL)
		return 0;
	SDL_RWread(file, &score, sizeof(score), 1);
	SDL_RWclose(file);
	return score;
}

//saving best result
void save_result(int result)
{
	int score = 0;
	SDL_RWops* file = SDL_RWFromFile("result.bin", "r+b");

	//if file don`t contain any data write current result and exit from function
	if (file == NULL)
	{
		file = SDL_RWFromFile("result.bin", "w+b");
		SDL_RWwrite(file, &score, sizeof(score), 1);
		SDL_RWclose(file);
		return;
	}

	//else read early best result
	SDL_RWread(file, &score, sizeof(score), 1);
	SDL_RWclose(file);

	//and compare results
	if (result > score)
	{
		file = SDL_RWFromFile("result.bin", "w+b");
		SDL_RWwrite(file, &result, sizeof(score), 1);
		SDL_RWclose(file);
	}
}
