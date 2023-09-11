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
}


void MainMenu::update() {
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
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