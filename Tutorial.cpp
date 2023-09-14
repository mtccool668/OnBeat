#include "Tutorial.h"

Tutorial::Tutorial(SDL_Renderer* renderer) : renderer(renderer) {

	buttonState = NORMAL;
	level = BEGINNER;
	buttonName = NONE;
	clicks = 0;
	repeat = false;
}

ButtonName Tutorial::getButton(int mouseX, int mouseY) {

	return NONE;

}

void Tutorial::update() {
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		
		switch (event.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				buttonState = PRESS;
				break;
			}

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_h:
				clicks += 1;
				printf("clicks: %d\n", clicks);
				break;
			}
		}

	}
}

void Tutorial::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, bkgTextures[0], nullptr, nullptr);

	SDL_Rect drect = { 0, 300, 1011, 1145 };
	SDL_RenderCopy(renderer, characterTextures[0], nullptr, &drect);

	drect = { (SCREEN_WIDTH - 950) / 2, 50, 950, 310 };
	SDL_RenderCopy(renderer, fontTextures[0], nullptr, &drect);

	drect = { (SCREEN_WIDTH - 1519) / 2, 500, 1519, 309 };
	if (clicks == 0 && !repeat) {
		SDL_RenderCopy(renderer, entityTextures[0], nullptr, &drect);
	}
	else if (clicks >= 1 && clicks <= 16) {
		SDL_Rect quarterRect = { 0, 0, 1519 - (clicks * 49 * 2), 309 };
		drect = { ((SCREEN_WIDTH - 1519) / 2) + (49 * clicks * 2), 500, 1519 - (clicks * 49 * 2), 309 };
		SDL_RenderCopy(renderer, entityTextures[1], &quarterRect, &drect);
	}
	else if (clicks > 16) {
		repeat = true;
		SDL_RenderCopy(renderer, entityTextures[1], nullptr, &drect);
		clicks = 0;
	}
	
	
}

screen Tutorial::getScreen() {
	if (buttonName == NONE && buttonState == PRESS) {
		return MAIN_MENU;
	}
	return TUTORIAL;
}

void Tutorial::reset() {
	SDL_RenderClear(renderer);
	buttonState = NORMAL;
	clicks = 0;
	repeat = false;
}
