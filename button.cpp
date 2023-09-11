#include "button.h"
#include "SDL2.h"



Button::Button(SDL_Renderer* renderer, const std::string& defaultTexturePath, const std::string& hoverTexturePath, int x, int y, int w, int h) :
	renderer(renderer), defaultTexturePath(defaultTexturePath), hoverTexturePath(hoverTexturePath), x(x), y(y), w(w), h(h) {

	if (!std::filesystem::exists(defaultTexturePath)){
		printf("can't find default texture path");
	}
	
	if (!std::filesystem::exists(hoverTexturePath)) {
		printf("can't find hoverTexture path");
	}
	printf("i got here");
	defaultButton = loadTexture(defaultTexturePath);
	hoverButton = loadTexture(hoverTexturePath);
	if (!defaultButton || !hoverButton) {
		printf("Failed to load button textures.\n");
	}
}

	
Button::~Button() {
	SDL_DestroyTexture(defaultButton);
	SDL_DestroyTexture(hoverButton);
}

void Button::render() {
	SDL_Rect dstRect = { x, y, w, h };
	SDL_Texture* textureToRender = (hovered) ? hoverButton : defaultButton;
	SDL_RenderCopy(renderer, textureToRender, nullptr, &dstRect);
}

bool Button::isHovered(int mouseX, int mouseY) const {
	return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
}
void Button::handleMouseHover(int mouseX, int mouseY) {
	hovered = (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
}

SDL_Texture* Button::loadTexture(const std::string& texturePath) {
	SDL_Surface* surface = IMG_Load(texturePath.c_str());
	if (!surface) {
		throw std::runtime_error("Failed to load image: " + texturePath);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	return texture;
}
