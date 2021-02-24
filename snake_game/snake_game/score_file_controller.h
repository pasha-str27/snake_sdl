#pragma once

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

void save_result(int result)
{
	int score = 0;
	SDL_RWops* file = SDL_RWFromFile("result.bin", "r+b");
	if (file == NULL)
	{
		file = SDL_RWFromFile("result.bin", "w+b");
		SDL_RWwrite(file, &score, sizeof(score), 1);
		SDL_RWclose(file);
		return;
	}
	SDL_RWread(file, &score, sizeof(score), 1);
	SDL_RWclose(file);

	if (result > score)
	{
		file = SDL_RWFromFile("result.bin", "w+b");
		SDL_RWwrite(file, &result, sizeof(score), 1);
		SDL_RWclose(file);
	}
}
