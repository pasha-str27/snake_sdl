#include "game_manager.h"
#include <ctime>

#define screen_height 1000
#define screen_width 1580

int main(int arc, char** argv)
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	game_manager game(screen_height,screen_width);

	game.init();
	game.play();
	game.exit();



	SDL_Quit();
	IMG_Quit();

	TTF_Quit();

	return 0;
}