#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

enum ButtonState {
	NORMAL,
	HOVER,
	PRESS
};

enum ButtonName {
	NONE,
	PLAY,
	EXIT,
	SETTINGS,
	SHOP,
	PROFILE,
	PHONE
};

class Button
{
public:
	Button(SDL_Renderer* renderer, const std::string& defaultTexturePath, const std::string& hoverTexturePath, int x, int y, int w, int h);
	~Button();

	
	void render();
	bool isHovered(int mouseX, int mouseY) const;
	void handleMouseHover(int mouseX, int mouseY);
	SDL_Texture* loadTexture(const std::string& imagePath);



private:
	SDL_Renderer* renderer;
	const std::string& defaultTexturePath;
	const std::string& hoverTexturePath;
	SDL_Texture* defaultButton;
	SDL_Texture* hoverButton;
	int x, y, w, h;
	bool hovered;

};

