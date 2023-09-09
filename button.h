#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Button
{
public:
	Button(SDL_Renderer* renderer, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, int x, int y, int w, int h);
	~Button();
	
	void render();
	bool isClicked(int mouseX, int mouseY) const;
	void handleMouseHover(int mouseX, int mouseY);

private:
	SDL_Renderer* renderer;
	SDL_Texture* defaultTexture;
	SDL_Texture* hoverTexture;
	int x, y, w, h;
	bool isHovered;

	SDL_Texture* loadTexture(const std::string& imagePath);
};

