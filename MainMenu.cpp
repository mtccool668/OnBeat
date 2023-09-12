#include "MainMenu.h"


MainMenu::MainMenu(SDL_Renderer* renderer, const std::string& imgPath) : Screen(renderer, imgPath), renderer(renderer), imgPath(imgPath) {
    SDL_Surface* bkgSurface = IMG_Load(imgPath.c_str());
    if (!renderer) {
        printf("can't use renderer");
    }
    bkgTexture = SDL_CreateTextureFromSurface(renderer, bkgSurface);
    SDL_FreeSurface(bkgSurface);
    if (!std::filesystem::exists(imgPath)) {
        printf("can't find default image path");
    }

	ID = 0;
}

std::vector<SDL_Rect> MainMenu::loadButtons(const std::string imgPath, int width, int height) {
	SDL_Surface* spriteSurface = SDL_LoadBMP(imgPath.c_str());
	SDL_Texture* spriteTexture = nullptr;

	if (spriteSurface) {
		spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
		SDL_FreeSurface(spriteSurface);
	}
	else {
		printf("I cant seem to load the buttons");
	}

	//Create sprite rectangeles (depending on grid size)
	const int imgCount = 4;
	std::vector<SDL_Rect> spriteBoxes(imgCount, { 0, 0, 0, 0 });
	int sWidth = width / (imgCount * (int)sqrt(imgCount));
	int sHeight = height / imgCount;

	for (int i = 0; i < imgCount; i++) {
		spriteBoxes[i].x = (i % imgCount) * sWidth;
		spriteBoxes[i].y = (i / imgCount) * sHeight;

		if (i == 0) {
			SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[i], &spriteBoxes[0]);
		}
		else if (i == 1) {
			SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[0], &spriteBoxes[0]);
		}
		else if (i == 2) {
			SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[0], &spriteBoxes[0]);
		}
		else if (i == 3) {
			SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[0], &spriteBoxes[0]);
		}

	}

	return spriteBoxes;
}

void MainMenu::update() {
	SDL_Event event;
	bool mouseDown, mousePressed;
	
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
				mouseDown = true;
				mousePressed = true;
				printf("clicked");
				
			}
			
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		}
	}
}

void MainMenu::render(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bkgTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void MainMenu::handleInput(SDL_Event& event) {
    return;
}

int MainMenu::get() {
	return ID;
}