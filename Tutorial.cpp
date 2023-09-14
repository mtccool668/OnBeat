#include "Tutorial.h"

Tutorial::Tutorial(SDL_Renderer* renderer, const std::string& bkgPath, const std::string& titlePath) : renderer(renderer),
bkgPath(bkgPath), titlePath(titlePath) {
	SDL_Surface* bkgSurface = IMG_Load(bkgPath.c_str());
	SDL_Surface* titleSurface = IMG_Load(titlePath.c_str());
	if (!renderer) {
		printf("can't use renderer");
	}

	if (!std::filesystem::exists(bkgPath) || !std::filesystem::exists(titlePath)) {
		printf("can't find default image path");
	}
	bkgTexture = SDL_CreateTextureFromSurface(renderer, bkgSurface);
	titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
	SDL_FreeSurface(bkgSurface);
	SDL_FreeSurface(titleSurface);

	buttonState = NORMAL;
	level = BEGINNER;
	buttonName = NONE;

	sheet = nullptr;

}

void Tutorial::loadTextures(SDL_Renderer* renderer, const std::string imgPath, int width, int height) {
	std::cout << imgPath << "\n";
	SDL_Surface* spriteSurface = IMG_Load(imgPath.c_str());
	SDL_Texture* spriteTexture = nullptr;

	if (spriteSurface) {
		spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
		SDL_FreeSurface(spriteSurface);
	}
	else {
		printf("I cant seem to load the textures");
	}

	sheet = spriteTexture;


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
	SDL_RenderCopy(renderer, bkgTexture, nullptr, nullptr);
	SDL_DestroyTexture(bkgTexture);
	
	SDL_Texture* girlTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/charMC.png"));
	SDL_Rect girlRect = { 0, 300, 1011, 1145 };
	SDL_RenderCopy(renderer, girlTexture, nullptr, &girlRect);
	SDL_DestroyTexture(girlTexture);
	
	SDL_Rect titleRect = { (WINDOW_WIDTH - 950) / 2, 50, 950, 310 };
	SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
	SDL_DestroyTexture(titleTexture);
	
	SDL_Rect quarterRect = { (WINDOW_WIDTH - 1519) / 2, 500, 1519, 309 };
	SDL_RenderCopy(renderer, sheet, nullptr, &quarterRect);
	SDL_DestroyTexture(sheet);
	
}

screen Tutorial::get() {
	if (buttonName == NONE && buttonState == PRESS) {
		return MAIN_MENU;
	}
	return TUTORIAL;
}

void Tutorial::reset() {
	SDL_RenderClear(renderer);
	buttonState = NORMAL;
}
