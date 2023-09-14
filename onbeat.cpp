#define _CRTDBG_MAP_ALLOC
#include "SDL2.h"
#include "metronome.h"
#include "button.h"
#include "MainMenu.h"
#include "VideoPlayer.h"
#include "GameLogic.h"
#include "Tutorial.h"
#include <crtdbg.h>



int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	startGame(window, renderer);
	window = getWindow();
	renderer = getRenderer();
	printf("finished creating game\n");
	SDL_SetWindowInputFocus(window);
	
	/*Create button and load textures
	(TEST 1)
	Button button(renderer, "images/left.bmp", "images/down.bmp", 100, 100, 200, 100);
	button.render();

	Button exit(renderer, "images/right.bmp", "images/up.bmp", 900, 900, 200, 100);
	exit.render();
	*/

	//Load background music
	Mix_Music* bkgMusic = Mix_LoadMUS("music/bkg_music.mp3");
	if (!bkgMusic) {
		printf("music error\n");
	}
	
	
	//Main Menu Screen
	MainMenu mainMenu(renderer, "images/home_bkg.png", "images/title.png");
	mainMenu.loadTextures(renderer, "images/menu_sheet.png", 830, 294);

	//Tutorial Screen
	Tutorial tutorial(renderer, "images/home_bkg.png", "images/title.png");
	tutorial.loadTextures(renderer, "images/tutorial1.png", 1519, 309);
	//Level Screen
	


	bool quit = false;

	screen screenID = MAIN_MENU;
	while (!quit) {
		
		if (screenID == MAIN_MENU) {
			tutorial.reset();
			mainMenu.update();
			mainMenu.render(renderer);
			screenID = mainMenu.get();
		}

		else if (screenID == TUTORIAL) {
			mainMenu.reset();
			tutorial.update();
			tutorial.render(renderer);
			screenID = tutorial.get();
		}

		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	_CrtDumpMemoryLeaks();
	SDL_Quit();
	return 1;

}