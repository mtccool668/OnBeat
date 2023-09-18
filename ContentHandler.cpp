#include "ContentHandler.h"


ContentHandler::ContentHandler(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT) : window(NULL), renderer(NULL) {
	
	//Create Window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	printf("lets get started\n");
	if (window == nullptr) {
		printf("something went wrong smh\n");
	}


	//Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

SDL_Texture* ContentHandler::loadFont(const char* filePath, SDL_Color textColor, int fontSize) {
	TTF_Font* font = TTF_OpenFont(filePath, fontSize);
	if (!font) {
		printf("can't load font\n");
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Press anywhere to start!", textColor);
	if (!textSurface) {
		printf("can't load text surface\n");
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture) {
		printf("can't render text texture\n");
	}
	int textWidth, textHeight;
	if (TTF_SizeText(font, "Press anywhere to start!", &textWidth, &textHeight) != 0) {
		printf("can't get dimensions of font box\n");
	}
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

	return textTexture;
}


void ContentHandler::createGameTextures() {
	//PNG textures
	SDL_Texture* bkgTexture = loadTexture("images/home_bkg.png");
	SDL_Texture* girlTexture = loadTexture("images/charMC.png");
	SDL_Texture* titleTexture = loadTexture("images/title.png");
	SDL_Texture* menuSheet = loadTexture("images/menu_sheet.png");
	SDL_Texture* tutorial1 = loadTexture("images/tutorial1.png");
	SDL_Texture* girl_sheet = loadTexture("images/girl_sheet.png");

	//FONT textures
	SDL_Texture* shortbaby = loadFont("fonts/shortbaby.ttf", { 0, 0, 0 }, 18);



	//Background Textures
	bkgTextures[0] = bkgTexture;
	
	//Character Textures
	characterTextures[0] = girl_sheet;
	
	//Font Textures
	fontTextures[0] = titleTexture;
	fontTextures[1] = shortbaby;
	
	//Button Textures
	buttonTextures[0] = menuSheet;
	
	//Entity Textures
	entityTextures[0] = tutorial1;
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