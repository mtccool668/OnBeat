#include "SDL2.h"
#include "metronome.h"
#include "button.h"
#include "screen.h"
#include "ScreenManager.h"
#include "MainMenu.h"
#include "VideoPlayer.h"
#include "GameLogic.h"

//Key press surfaces constants

const int TARGET_FPS = 240;
const int FRAME_TIME = 1000 / TARGET_FPS;

enum screen { MAIN_MENU, SETTINGS, GAME };


int main(int argc, char* argv[]) {
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	startGame(window, renderer);
	window = getWindow();
	renderer = getRenderer();
	printf("finished creating game\n");

	/*Create button and load textures
	(TEST 1)
	Button button(renderer, "images/left.bmp", "images/down.bmp", 100, 100, 200, 100);
	button.render();

	Button exit(renderer, "images/right.bmp", "images/up.bmp", 900, 900, 200, 100);
	exit.render();
	*/

	//Screen Manager
	ScreenManager screenManager(renderer);
	
	//Main Menu Screen
	std::shared_ptr<Screen> baseMainMenu = std::make_shared<MainMenu>(renderer, "images/menu.jpg");
	std::shared_ptr<MainMenu> mainMenu = std::dynamic_pointer_cast<MainMenu>(baseMainMenu);
	
	
	mainMenu->loadTextures(renderer, "images/menu_sheet.png", 1794, 652);
	screenManager.pushScreen(mainMenu);


	//Level Screen
	//std::shared_ptr<Screen> levelMenu = std::make_shared<GameLevel>(renderer, "images/menu.jpg");
		

	/*gpress = Mix_LoadWAV("sounds/niga.wav");
	Metronome m1(60);
	m1.sendMsg();eee
	int bpm = m1.trackBPM();
	m1.playMetronome(bpm, gpress);
	*/


	bool quit = false;
	printf("i got here\n");

	int screenID = screenManager.getScreenID();
	while (!quit) {
		switch (screenID) {
		case MAIN_MENU:
			screenManager.updateScreen();
			screenManager.renderScreen();
		}

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 1;

}