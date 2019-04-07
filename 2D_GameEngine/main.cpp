#include "Game.h"

Game *game = nullptr;

int main(int argc, char * argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;	//Max time between frames

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("VealeNgine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		960, 960, false);
		
	while (game->running()) {

		frameStart = SDL_GetTicks();	//ms since SDL_Init


		game->handleEvents();
		game->update();
		game->render();

		//ms to handle events, update and render
		frameTime = SDL_GetTicks() - frameStart;

		//limit FPS to 60 (look at article for other (better) ways to do this
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}