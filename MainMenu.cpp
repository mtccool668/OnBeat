#include "MainMenu.h"


MainMenu::MainMenu(SDL_Renderer* renderer, const std::string& bkgPath) : Screen(renderer, bkgPath), renderer(renderer), bkgPath(bkgPath), sheet(nullptr) {
    SDL_Surface* bkgSurface = IMG_Load(bkgPath.c_str());
    if (!renderer) {
        printf("can't use renderer");
    }
    bkgTexture = SDL_CreateTextureFromSurface(renderer, bkgSurface);
    SDL_FreeSurface(bkgSurface);
    if (!std::filesystem::exists(bkgPath)) {
        printf("can't find default image path");
    }
	
	ID = 0;
	buttonState = NORMAL;
	buttonName = UNDEFINED;

	for (int i = 0; i < 4; ++i) {
		drects[i].x = 0;
		drects[i].y = 0;
		drects[i].w = 0;
		drects[i].h = 0;
	}

}

void MainMenu::loadTextures(SDL_Renderer* renderer, const std::string imgPath, int width, int height) {
	std::cout << imgPath << "\n";
	SDL_Surface* spriteSurface = IMG_Load(imgPath.c_str());
	SDL_Texture* spriteTexture = nullptr;

	if (spriteSurface) {
		spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
		SDL_FreeSurface(spriteSurface);
	}
	else {
		printf("I cant seem to load the buttons");
	}

	//Create sprite rectangeles (depending on grid size)
	const int gridSize = 2; //2x2, 4x4, 8x8, etc..
	std::vector<SDL_Rect> spriteRects(4);
	int sWidth = width / gridSize;
	int sHeight = height / gridSize;
	

	for (int i = 0; i < 4; ++i) {
		//Set sprite coordinates
		spriteRects[i].x = (i % gridSize) * sWidth;
		spriteRects[i].y = (i / gridSize) * sHeight;
		spriteRects[i].w = sWidth;
		spriteRects[i].h = sHeight;
	}
	
	drects[0] = { 0, 0, spriteRects[0].w, spriteRects[0].h };
	drects[1] = { 0, 0, spriteRects[1].w, spriteRects[1].h };
	drects[2] = { 500, 0, spriteRects[2].w, spriteRects[2].h };
	drects[3] = { 500, 0, spriteRects[2].w, spriteRects[2].h };

	
	srects = spriteRects;
	sheet = spriteTexture;
}


void MainMenu::update() {
	SDL_Event event;
	bool hovered = false;
	int mouseX, mouseY;
	bool mouseHover = false;

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
				break;
			}
		
				
			break;
		}

	}
	SDL_RenderClear(renderer);
	render(renderer);
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
	
	return UNDEFINED;

}

void MainMenu::render(SDL_Renderer* renderer) {
	
	SDL_RenderCopy(renderer, bkgTexture, nullptr, nullptr);
	

	printf("%d\n", buttonState);

	switch (buttonState) {
	case NORMAL:
	
		SDL_RenderCopy(renderer, sheet, &srects[0], &drects[0]); // Render Play button
			
		SDL_RenderCopy(renderer, sheet, &srects[2], &drects[2]); // Render Exit button
		
		break;
	
	case HOVER:
		switch (buttonName) {
		case PLAY:
			SDL_RenderCopy(renderer, sheet, &srects[1], &drects[1]); // Render Play button
			SDL_RenderCopy(renderer, sheet, &srects[2], &drects[2]);
			break;
		case EXIT:
			SDL_RenderCopy(renderer, sheet, &srects[3], &drects[3]); // Render Exit button
			SDL_RenderCopy(renderer, sheet, &srects[0], &drects[0]);
			break;

		}
		
		break;
	
	case PRESS:
		switch (buttonName) {
		case PLAY:
			SDL_RenderCopy(renderer, sheet, &srects[1], &drects[1]); // Render Play button
			SDL_RenderCopy(renderer, sheet, &srects[2], &drects[2]);
			break;
		case EXIT:
			SDL_RenderCopy(renderer, sheet, &srects[3], &drects[3]); // Render Exit button
			SDL_RenderCopy(renderer, sheet, &srects[0], &drects[0]);
			break;

		}
		break;

	}
	
	
	SDL_RenderPresent(renderer);
}	

int MainMenu::get() {
	return ID;
}