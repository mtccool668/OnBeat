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

const int TARGET_FPS = 240;
const int FRAME_TIME = 1000 / TARGET_FPS;

int main(int argc, char* argv[]) {
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	startGame(window, renderer);
	window = getWindow();
	renderer = getRenderer();

	/*Create button and load textures
	(TEST 1)*/
	Button button(renderer, "images/left.bmp", "images/down.bmp", 100, 100, 200, 100);
	button.render();

	Button exit(renderer, "images/right.bmp", "images/up.bmp", 900, 900, 200, 100);
	exit.render();
	

	ScreenManager screenManager(renderer);
	std::shared_ptr<Screen> loadingScreen = std::make_shared<MainMenu>(renderer, "images/menu.jpg");
	
	


	/*gpress = Mix_LoadWAV("sounds/niga.wav");
	Metronome m1(60);
	m1.sendMsg();eee
	int bpm = m1.trackBPM();
	m1.playMetronome(bpm, gpress);
	*/



	bool quit = false;
	SDL_Event event;
	int mouseX = 0;
	int	mouseY = 0;

	bool clicked = false;
	screenManager.pushScreen(loadingScreen);

	Uint32 currentTime, lastTime = 0;
	int deltaTime;

	while (!quit) {
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		
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
				switch(event.button.button) {
				
				case SDL_BUTTON_LEFT:
					mouseX = event.button.x;
					mouseY = event.button.y;

					if (button.isHovered(mouseX, mouseY)) {
						printf("button clicked");
						screenManager.popScreen();
						mouseX = 0;
						mouseY = 0;
					}
					if (exit.isHovered(mouseX, mouseY)) {
						printf("exit clicked");
						screenManager.pushScreen(loadingScreen);
					}
					break;
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_s:
					break;
				}
				break;
				
			}

			
		}

		SDL_RenderClear(renderer);
		screenManager.renderScreen();
		button.render();
		exit.render();
		SDL_RenderPresent(renderer);

		if (deltaTime < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - deltaTime);
		}

		lastTime = currentTime;

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 1;

}