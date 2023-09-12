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
	
	SDL_RenderCopy(renderer, bkgTexture, nullptr, nullptr);
	
	ID = 0;
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

	/*
	SDL_Rect srect0 = { 0, 0, 897, 326 };
	SDL_Rect srect1 = { 897, 0, 897, 326 };
	SDL_Rect srect2 = { 0, 326, 897, 326 };
	SDL_Rect srect3 = { 897, 326, 897, 326 };
	
	SDL_Rect drect0 = { 0, 0, 897, 326 };
	SDL_Rect drect1 = { 897, 0, 897, 326 };
	SDL_Rect drect2 = { 0, 326, 897, 326 };
	SDL_Rect drect3 = { 897, 326, 897, 326 };

	SDL_RenderCopy(renderer, spriteTexture, &srect0, &drect0);
	SDL_RenderCopy(renderer, spriteTexture, &srect1, &drect1);
	SDL_RenderCopy(renderer, spriteTexture, &srect2, &drect2);
	SDL_RenderCopy(renderer, spriteTexture, &srect3, &drect3);
	
	SDL_RenderPresent(renderer);
	*/

	//Create sprite rectangeles (depending on grid size)
	const int imgCount = 4;
	const int gridSize = (int)sqrt(imgCount); //2x2, 4x4, 8x8, etc..
	std::vector<SDL_Rect> spriteBoxes(imgCount);
	int sWidth = width / gridSize;
	int sHeight = height / gridSize;

	for (int i = 0; i < imgCount; i++) {
		spriteBoxes[i].x = (i % gridSize) * sWidth;
		spriteBoxes[i].y = (i / gridSize) * sHeight;
		spriteBoxes[i].w = sWidth;
		spriteBoxes[i].h = sHeight;
	}

	
	SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[0], &spriteBoxes[0]);
	SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[1], &spriteBoxes[1]);
	SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[2], &spriteBoxes[2]);
	SDL_RenderCopy(renderer, spriteTexture, &spriteBoxes[3], &spriteBoxes[3]);

	SDL_RenderPresent(renderer);
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
    SDL_RenderPresent(renderer);
}

void MainMenu::handleInput(SDL_Event& event) {
    return;
}

int MainMenu::get() {
	return ID;
}