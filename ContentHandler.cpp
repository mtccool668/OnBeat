#include "ContentHandler.h"


ContentHandler::ContentHandler(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT) : window(NULL), renderer(NULL) {
	
	//Create Window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	printf("lets get started\n");
	if (window == nullptr) {
		printf("something went wrong smh\n");
	}


	//Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("SDL_CreateRenderer error\n");
	}

}

SDL_Texture* ContentHandler::loadTexture(const char* filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);
	if (!texture) {
		printf("failed to load texture\n");
	}
	
	return texture;
}

void ContentHandler::createGameTextures() {
	SDL_Texture* bkgTexture = loadTexture("images/home_bkg.png");
	SDL_Texture* girlTexture = loadTexture("images/charMC.png");
	SDL_Texture* titleTexture = loadTexture("images/title.png");
	SDL_Texture* menuSheet = loadTexture("images/menu_sheet.png");
	SDL_Texture* tutorial1_base = loadTexture("images/tutorial1_base.png");
	SDL_Texture* tutorial1 = loadTexture("images/tutorial1.png");

	//Background Textures
	bkgTextures[0] = bkgTexture;
	
	//Character Textures
	characterTextures[0] = girlTexture;
	
	//Font Textures
	fontTextures[0] = titleTexture;
	
	//Button Textures
	buttonTextures[0] = menuSheet;
	
	//Entity Textures
	entityTextures[0] = tutorial1_base;
	entityTextures[1] = tutorial1;
}

SDL_Renderer* ContentHandler::getRenderer() const{
	return renderer;
}

SDL_Window* ContentHandler::getWindow() const{
	return window;
}

void ContentHandler::closeGame(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ContentHandler::destroyTextureArray(SDL_Texture* arr[], int size) {
	for (int i = 0; i < size; ++i) {
		SDL_DestroyTexture(arr[i]);
	}
}

void ContentHandler::destroyGameTextures() {
	destroyTextureArray(entityTextures, 4);
	destroyTextureArray(bkgTextures, 4);
	destroyTextureArray(characterTextures, 4);
	destroyTextureArray(fontTextures, 4);
	destroyTextureArray(buttonTextures, 4);
}

ContentHandler::~ContentHandler() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}