#include "Tutorial.h"

Tutorial::Tutorial(SDL_Renderer* renderer) : renderer(renderer) {

	buttonState = NORMAL;
	level = BEGINNER;
	buttonName = NONE;
	leftClicks = 0;
	rightClicks = 0;
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
			case SDLK_j:
				if (rightClicks == 16) {
					rightClicks = 0;
					repeat = true;
				}
				rightClicks += 1;
				break;

			case SDLK_f:
				if (leftClicks == 16) {
					leftClicks = 0;
					repeat = true;
				}
				leftClicks += 1;
				break;
			}

		

		}

	}
}

void Tutorial::render300() {

	int frameWidth = 1435 / 5;
	int frameHeight = 1224 / 3;

	for (int col = 0; col < 4; ++col) {
		clips300[col].x = col * frameWidth;
		clips300[col].y = 0;
		clips300[col].w = frameWidth;
		clips300[col].h = frameHeight;
	}

}

void Tutorial::animate300(SDL_Renderer* renderer) {

	if (rightClicks % 4 == 0) {
		SDL_Rect* currentClip = &clips300[clips300_frame / 5];

		SDL_Rect drect = { (SCREEN_WIDTH - currentClip->w) / 2, 100, 287, 408 };
		SDL_RenderCopy(renderer, characterTextures[0], currentClip, &drect);

		SDL_RenderPresent(renderer);


		++clips300_frame;
		if (clips300_frame / 5 >= 10) {
			clips300_frame = 0;
		}
	}
}

	


void Tutorial::renderAssets(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, bkgTextures[0], nullptr, nullptr);

	SDL_Rect drect = { (SCREEN_WIDTH - 950) / 2, 50, 950, 310 };
	SDL_RenderCopy(renderer, fontTextures[0], nullptr, &drect);
}

void Tutorial::renderLeft(SDL_Renderer* renderer) {
	SDL_Rect drect = { 0, 300, 1011, 1145 };
	drect = { (SCREEN_WIDTH - 1519) / 2, 800, 1519, 309 };
	if (leftClicks == 0) {
		SDL_RenderCopy(renderer, entityTextures[0], nullptr, &drect);
	}
	else if (leftClicks >= 1 && leftClicks <= 16) {
		SDL_Rect quarterRect = { 0, 0, 1519 - ((leftClicks-1) * 49 * 2), 309 };
		drect = { ((SCREEN_WIDTH - 1519) / 2) + (49 * (leftClicks-1) * 2), 800, 1519 - ((leftClicks-1) * 49 * 2), 309 };
		SDL_RenderCopy(renderer, entityTextures[0], &quarterRect, &drect);
	}
}

void Tutorial::renderRight(SDL_Renderer* renderer) {
	SDL_Rect drect = { 0, 300, 1011, 1145 };
	drect = { (SCREEN_WIDTH - 1519) / 2, 500, 1519, 309 };
	if (rightClicks == 0) {
		SDL_RenderCopy(renderer, entityTextures[0], nullptr, &drect);
	}
	else if (rightClicks >= 1 && rightClicks <= 16) {
		SDL_Rect quarterRect = { 0, 0, 1519 - ((rightClicks-1) * 49 * 2), 309 };
		drect = { ((SCREEN_WIDTH - 1519) / 2) + (49 * (rightClicks-1) * 2), 500, 1519 - ((rightClicks-1) * 49 * 2), 309 };
		SDL_RenderCopy(renderer, entityTextures[0], &quarterRect, &drect);
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
	leftClicks = 0;
	rightClicks = 0;
	repeat = false;
}
