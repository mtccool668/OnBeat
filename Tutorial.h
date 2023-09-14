#pragma once
#include "screen.h"
#include "button.h"
#include "graphics.h"
#include "gamelogic.h"


enum LEVEL {
	BEGINNER,
	MEDIUM,
	HARD,
	EXPERT,
};

class Tutorial : public Screen
{
public:
	Tutorial(SDL_Renderer* renderer, const std::string& bkgPath, const std::string& titlePath);
	void update() override;
	ButtonName getButton(int mouseX, int mouseY);
	void render(SDL_Renderer* renderer) override;
	screen get();
	void reset();
	
private:
	SDL_Renderer* renderer;
	const std::string& bkgPath;
	const std::string& titlePath;
	SDL_Texture* bkgTexture;
	SDL_Texture* titleTexture;
	SDL_Texture* sheet;
	int ID;

	std::vector<SDL_Rect> srects;
	SDL_Rect drects[4];
	ButtonState buttonState;
	ButtonName buttonName;







private:
	LEVEL level;
};

