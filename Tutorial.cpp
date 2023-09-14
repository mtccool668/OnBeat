#include "Tutorial.h"

Tutorial::Tutorial(SDL_Renderer* renderer) : renderer(renderer) {

	buttonState = NORMAL;
	level = BEGINNER;
	buttonName = NONE;

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


			break;
		}

	}
}

void Tutorial::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, bkgTextures[0], nullptr, nullptr);

	SDL_Rect girlRect = { 0, 300, 1011, 1145 };
	SDL_RenderCopy(renderer, characterTextures[0], nullptr, &girlRect);

	SDL_Rect titleRect = { (SCREEN_WIDTH - 950) / 2, 50, 950, 310 };
	SDL_RenderCopy(renderer, fontTextures[0], nullptr, &titleRect);

	SDL_Rect quarterRect = { (SCREEN_WIDTH - 1519) / 2, 500, 1519, 309 };
	SDL_RenderCopy(renderer, entityTextures[0], nullptr, &quarterRect);
	
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
}
