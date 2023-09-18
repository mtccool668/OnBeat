#pragma once
#include "button.h"
#include "graphics.h"
#include "ContentHandler.h"
#include "assets.h"


enum LEVEL {
	BEGINNER,
	MEDIUM,
	HARD,
	EXPERT,
};

class Tutorial
{
public:
	Tutorial(SDL_Renderer* renderer);
	void update();
	ButtonName getButton(int mouseX, int mouseY);
	void animate300(SDL_Renderer* renderer);
	void render300();
	void renderButtons();
	void renderAssets(SDL_Renderer* renderer);
	void renderLeft(SDL_Renderer* renderer);
	void renderRight(SDL_Renderer* renderer);
	screen getScreen();
	void reset();
	
private:
	SDL_Renderer* renderer;
	ButtonState buttonState;
	ButtonName buttonName;
	LEVEL level;
	int leftClicks;
	int rightClicks;
	bool repeat;

	//SDL_Rect srects[4];
	//SDL_Rect drects[4];
};

