#include "SDL2.h"
#include "metronome.h"
#include "button.h"
#include "MainMenu.h"
#include "ContentHandler.h"
#include "Tutorial.h"
#include "assets.h"
#include "playTutorial.h"


bool init() {
	//Start SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("something went wrong: %s\n", SDL_GetError());
	}
	if (!(IMG_Init(IMG_INIT_PNG))) {
		printf("IMG_init has failed\n");
	}
	//Open SDL_Mixer (audio program)
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 64) < 0) {
		printf("SDL_mixer bad: %s\n", Mix_GetError());
	}

	//open ttf font
	if (TTF_Init() < 0) {
		return 1;
	}

	return true;

}

int main(int argc, char* argv[]) {
	if (!init()) {
		printf("can't start game uh oh\n");
		return -1;
	}

	ContentHandler contentHandler("Onbeat", SCREEN_WIDTH, SCREEN_HEIGHT);
	contentHandler.createGameTextures();
	SDL_Window* window = contentHandler.getWindow();
	SDL_Renderer* renderer = contentHandler.getRenderer();
	
	printf("finished creating game\n");
	SDL_SetWindowInputFocus(window);
	
	//Load background music
	Mix_Music* bkgMusic = Mix_LoadMUS("music/bkg_music.mp3");
	if (Mix_PlayMusic(bkgMusic, -1) == -1) {
		printf("music playback error: %s\n", Mix_GetError());
	}

	//Main Menu Screen
	MainMenu mainMenu(renderer);

	//Tutorial Screen
	Tutorial tutorial(renderer);
	playTutorial();
	//Level Screen
	
	bool quit = false;
	int frame = 0;
	screen screenID = MAIN_MENU;
	while (!quit) {
		switch (screenID) {
		case MAIN_MENU:
			tutorial.reset();
			mainMenu.update();
			mainMenu.render(renderer);
			screenID = mainMenu.getScreen();
			break;

		case TUTORIAL:
			mainMenu.reset();
			tutorial.update();
			tutorial.renderAssets(renderer);
			tutorial.renderLeft(renderer);
			tutorial.renderRight(renderer);
			tutorial.render300();
			tutorial.animate300(renderer);
			screenID = tutorial.getScreen();
		}

		SDL_RenderPresent(renderer);
	}
	SDL_QuitSubSystem(SDL_INIT_VIDEO && SDL_INIT_AUDIO);
	contentHandler.destroyGameTextures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return 1;

}