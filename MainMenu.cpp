#include "MainMenu.h"



MainMenu::MainMenu(SDL_Renderer* renderer) : renderer(renderer), srects{ 0 }, drects{ 0 } {
    
	buttonState = NORMAL;
	buttonName = NONE;
	screenID = MAIN_MENU;
	
}

void MainMenu::update() {
	SDL_Event event;
	bool hovered = false;
	int mouseX, mouseY;
	bool mouseHover = false;
	bool pressed = false;

	while (SDL_PollEvent(&event))
	{
		SDL_GetMouseState(&mouseX, &mouseY);
		switch (event.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			break;

		case SDL_MOUSEMOTION:
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			for (int i = 0; i < 4; ++i) {
				if (mouseX >= drects[i].x && mouseX <= drects[i].x + drects[i].w
					&& mouseY >= drects[i].y && mouseY <= drects[i].y + drects[i].h) {
					buttonState = HOVER;
					buttonName = getButton(mouseX, mouseY);
					hovered = true;
					break;
				}
			}
			if (!hovered) {
				buttonState = NORMAL;
			}

			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				mouseX = event.button.x;
				mouseY = event.button.y;
				for (int i = 0; i < 4; ++i) {
					if (mouseX >= drects[i].x && mouseX <= drects[i].x + drects[i].w
						&& mouseY >= drects[i].y && mouseY <= drects[i].y + drects[i].h) {
						buttonState = PRESS;
						buttonName = getButton(mouseX, mouseY);
						hovered = true;
						printf("clicked play button\n");
						break;
					}
				}

				if (!hovered) {
					buttonState = NORMAL;
				}
				if (buttonState == PRESS) {
					printf("i got here\n");
				}
				if (buttonName == EXIT) {
					SDL_Delay(1000);
					SDL_QuitSubSystem(SDL_INIT_VIDEO);
					SDL_QuitSubSystem(SDL_INIT_AUDIO);
					SDL_Quit();
				}
				break;
			}


			break;
		}

	}
}

void MainMenu::render(SDL_Renderer* renderer) {
	//Create sprite rectangeles (depending on grid size)
	int gridSize = 2; //2x2, 4x4, 8x8, etc..
	int sWidth = 830 / gridSize;
	int sHeight = 294 / gridSize;



	for (int i = 0; i < 4; ++i) {
		//Set sprite coordinates
		srects[i].x = (i % gridSize) * sWidth;
		srects[i].y = (i / gridSize) * sHeight;
		srects[i].w = sWidth;
		srects[i].h = sHeight;
	}

	drects[0] = { (SCREEN_WIDTH - sWidth) / 2, 540, srects[0].w, srects[0].h };
	drects[1] = { (SCREEN_WIDTH - sWidth) / 2, 540, srects[1].w, srects[1].h };
	drects[2] = { (SCREEN_WIDTH - sWidth) / 2, 810, srects[2].w, srects[2].h };
	drects[3] = { (SCREEN_WIDTH - sWidth) / 2, 810, srects[2].w, srects[2].h };

	SDL_RenderCopy(renderer, bkgTextures[0], nullptr, nullptr);
	SDL_Rect titleRect = { (SCREEN_WIDTH - 950) / 2, 50, 950, 310 };
	SDL_RenderCopy(renderer, fontTextures[0], nullptr, &titleRect);

	switch (buttonState) {
	case NORMAL:
		SDL_RenderCopy(renderer, buttonTextures[0], &srects[0], &drects[0]); // Render Play button
		SDL_RenderCopy(renderer, buttonTextures[0], &srects[2], &drects[2]); // Render Exit butto
		break;

	case HOVER:
		switch (buttonName) {
		case PLAY:
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[1], &drects[1]); // Render Play button
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[2], &drects[2]);
			break;
		case EXIT:
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[3], &drects[3]); // Render Exit button
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[0], &drects[0]);
			break;
		}
		break;

	case PRESS:
		switch (buttonName) {
		case PLAY:
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[1], &drects[1]); // Render Play button
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[2], &drects[2]);
			break;
		case EXIT:
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[3], &drects[3]); // Render Exit button
			SDL_RenderCopy(renderer, buttonTextures[0], &srects[0], &drects[0]);
			break;

		}
		break;

	}

	
}	

ButtonName MainMenu::getButton(int mouseX, int mouseY) {
	if (mouseX >= drects[0].x && mouseX <= drects[0].x + drects[0].w
		&& mouseY >= drects[0].y && mouseY <= drects[0].y + drects[0].h) {
		return PLAY;
	}
	else if (mouseX >= drects[2].x && mouseX <= drects[2].x + drects[2].w
		&& mouseY >= drects[2].y && mouseY <= drects[2].y + drects[2].h) {

		return EXIT;
	}

	return NONE;

}

screen MainMenu::getScreen() {
	if (buttonName == PLAY && buttonState == PRESS) {
		return TUTORIAL;
	}
	return MAIN_MENU;
}

void MainMenu::reset() {
	SDL_RenderClear(renderer);
	buttonState = NORMAL;
	
}
