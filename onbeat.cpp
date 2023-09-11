#include "SDL2.h"
#include "metronome.h"
#include "button.h"
#include "screen.h"
#include "ScreenManager.h"
#include "MainMenu.h"
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <thread>
#include "VideoPlayer.h"
#include "GameLogic.h"

//Key press surfaces constants


int main(int argc, char* argv[]) {
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	startGame(window, renderer);
	window = getWindow();
	renderer = getRenderer();

	//Create button and load textures
	Button button(renderer, "images/left.bmp", "images/down.bmp", 100, 100, 200, 100);

	button.render();


	/*ScreenManager screenManager(renderer);
	std::unique_ptr<Screen> loadingScreen = std::make_unique<MainMenu>();
	screenManager.pushScreen(std::move(loadingScreen));
	*/


	/*gpress = Mix_LoadWAV("sounds/niga.wav");
	Metronome m1(60);
	m1.sendMsg();
	int bpm = m1.trackBPM();
	m1.playMetronome(bpm, gpress);
	*/



	bool quit = false;
	SDL_Event event;
	int mouseX = 0;
	int	mouseY = 0;

	while (!quit) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_MOUSEMOTION:
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				button.handleMouseHover(mouseX, mouseY);
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					mouseX = event.button.x;
					mouseY = event.button.y;
					if (button.isClicked(mouseX, mouseY)) {
						//printf("Button clicked!\n");
					}
				}
				break;
			}
			SDL_RenderClear(renderer);
			button.render();
			SDL_RenderPresent(renderer);
		}
		//screenManager.update();
		//screenManager.render();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}