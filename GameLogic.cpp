#include "GameLogic.h"

bool startGame(SDL_Window* window, SDL_Renderer* renderer) {
	//Start SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("something went wrong: %s\n", SDL_GetError());
		return 0;
	}
	//Create Window
	window = SDL_CreateWindow("OnBeat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	printf("lets get started\n");
	if (window == nullptr) {
		printf("something went wrong smh\n");
		return 0;
	}


	//Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("SDL_CreateRenderer error\n");
	}

	//Open SDL_Mixer (audio program)
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 64) < 0) {
		printf("SDL_mixer bad: %s\n", Mix_GetError());
		return 0;
	}

	return 1;

}

bool endGame(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}