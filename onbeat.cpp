#include "SDL2.h"
#include "metronome.h"
#include "button.h"
#include "screen.h"
#include "ScreenManager.h"
#include "MainMenu.h"
#include "VideoPlayer.h"
#include "GameLogic.h"
#include "Tutorial.h"



int main(int argc, char* argv[]) {
	
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
	
		
	//Screen Manager
	//ScreenManager screenManager(renderer);
	
	//Main Menu Screen
	//std::shared_ptr<Screen> baseMainMenu = std::make_shared<MainMenu>(renderer, "images/home_bkg.png", "images/title.png");
	//std::shared_ptr<MainMenu> mainMenu = std::dynamic_pointer_cast<MainMenu>(baseMainMenu);
	MainMenu mainMenu(renderer, "images/home_bkg.png", "images/title.png");
	mainMenu.loadTextures(renderer, "images/menu_sheet.png", 830, 294);
	printf("loaded textures");
	
	//Tutorial Screen
	//std::shared_ptr<Screen> baseTutorial = std::make_shared<Tutorial>(renderer, "images/home_bkg.png", "images/title.png");
	//std::shared_ptr<Tutorial> mainTutorial = std::dynamic_pointer_cast<Tutorial>(baseTutorial);
	Tutorial tutorial(renderer, "images/charMC.png", "images/title.png");

	
	
	//Level Screen
	//std::shared_ptr<Screen> levelMenu = std::make_shared<GameLevel>(renderer, "images/menu.jpg");
		

	/*gpress = Mix_LoadWAV("sounds/niga.wav");
	Metronome m1(60);
	m1.sendMsg();eee
	int bpm = m1.trackBPM();
	m1.playMetronome(bpm, gpress);
	*/


	bool quit = false;

	screen screenID = MAIN_MENU;
	while (!quit) {
		printf("%d\n", screenID);
		if (screenID == MAIN_MENU) {
			tutorial.reset();
			mainMenu.update();
			mainMenu.render(renderer);
			screenID = mainMenu.get();
		}

		if (screenID == TUTORIAL) {
			mainMenu.reset();
			tutorial.update();
			tutorial.render(renderer);
			screenID = tutorial.get();
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("ended game");
	return 1;

}