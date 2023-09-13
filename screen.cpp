#include "screen.h"

Screen::Screen(SDL_Renderer* renderer,const std::string& imgPath) : renderer(renderer), imgPath(imgPath) {
	SDL_Surface* bkgSurface = IMG_Load(imgPath.c_str());
	if (!bkgSurface) {
		std::cout << "can't load bkg img" << "\n";
	}
	bkgTexture = SDL_CreateTextureFromSurface(renderer, bkgSurface);
	SDL_FreeSurface(bkgSurface);

	if (!bkgTexture) {
		std::cout << "can't create bkg texture" << "\n";
	}

	ID = -1;
}

void Screen::update() {
	return;
}
void Screen::render(SDL_Renderer* renderer) {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bkgTexture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

int Screen::get() {
	return ID;
}
