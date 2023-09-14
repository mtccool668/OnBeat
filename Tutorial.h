#pragma once
#include "button.h"
#include "graphics.h"
#include "ContentHandler.h"
#include "textures.h"

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
	void render(SDL_Renderer* renderer);
	screen getScreen();
	void reset();
	
private:
	SDL_Renderer* renderer;
	ButtonState buttonState;
	ButtonName buttonName;
	LEVEL level;
	int clicks;
	bool repeat;
};

