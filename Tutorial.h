#pragma once
#include "button.h"
#include "graphics.h"
#include "gamelogic.h"


enum LEVEL {
	BEGINNER,
	MEDIUM,
	HARD,
	EXPERT,
};

class Tutorial
{
public:
	Tutorial(SDL_Renderer* renderer, const std::string& bkgPath, const std::string& titlePath);
	void update();
	ButtonName getButton(int mouseX, int mouseY);
	void loadTextures(SDL_Renderer* renderer, const std::string imgPath, int width, int height);
	void render(SDL_Renderer* renderer);
	screen get();
	void reset();
	
private:
	SDL_Renderer* renderer;
	const std::string& bkgPath;
	const std::string& titlePath;
	SDL_Texture* bkgTexture;
	SDL_Texture* titleTexture;
	SDL_Texture* sheet;

	ButtonState buttonState;
	ButtonName buttonName;







private:
	LEVEL level;
};

