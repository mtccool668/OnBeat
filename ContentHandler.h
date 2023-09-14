#pragma once
#include "SDL2.h"
#include "graphics.h"
#include "MainMenu.h"
#include "button.h"
#include "textures.h"

class ContentHandler {
public:
	
	ContentHandler(const char* titlePath, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	
	~ContentHandler();

	SDL_Texture* loadTexture(const char* filePath);

	void createGameTextures();

	SDL_Window* getWindow() const;

	SDL_Renderer* getRenderer() const;

	void destroyTextureArray(SDL_Texture* arr[], int size);

	void destroyGameTextures();

	void closeGame(SDL_Window* window, SDL_Renderer* renderer);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	
};



