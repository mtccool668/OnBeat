#include "GameLogic.h"
#include "SDL2.h"


struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
} GameSystems;

void startGame(SDL_Window* window, SDL_Renderer* renderer) {
	//Start SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("something went wrong: %s\n", SDL_GetError());
	}
	//Create Window
	window = SDL_CreateWindow("OnBeat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	printf("lets get started\n");
	if (window == nullptr) {
		printf("something went wrong smh\n");
	}


	//Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("SDL_CreateRenderer error\n");
	}

	//Open SDL_Mixer (audio program)
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 64) < 0) {
		printf("SDL_mixer bad: %s\n", Mix_GetError());
	}

	GameSystems.window = window;
	GameSystems.renderer = renderer;
}

SDL_Renderer* getRenderer() {
	return GameSystems.renderer;
}

SDL_Window* getWindow() {
	return GameSystems.window;
}

void endGame(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void discardAllEvents(bool gameFlag) {
	SDL_Event event;
	while (gameFlag) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				SDL_Quit();
				break;
			}
		}
	}
}

int countFolderContents(const std::string& folderPath) {
	namespace fs = std::filesystem;
	try {
		int count = 0;
		for (const auto& entry : fs::directory_iterator(folderPath)) {
			count++;
		}
		return count;
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1; // Return a negative value to indicate an error
	}
}