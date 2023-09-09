#include "button.h"
#include "onbeat.h"

Button::Button(SDL_Renderer* renderer, SDL_Texture* defaultTexture, SDL_Texture* hoverTexture, int x, int y, int w, int h) :
	renderer(renderer), defaultTexture(defaultTexture), hoverTexture(hoverTexture), x(x), y(y), w(w), h(h) {
	
	hoverTexture = defaultTexture;

}

Button::~Button() {
	SDL_DestroyTexture(defaultTexture);
}

void Button::render() {
	SDL_Rect dstRect = { x, y, w, h };
	SDL_Texture* textureToRender = (isHovered) ? hoverTexture : defaultTexture;
	SDL_RenderCopy(renderer, textureToRender, nullptr, &dstRect);
}

bool Button::isClicked(int mouseX, int mouseY) const {
	return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
}
void Button::handleMouseHover(int mouseX, int mouseY) {
	isHovered = (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
}

SDL_Texture* Button::loadTexture(const std::string& imagePath) {
	SDL_Surface* surface = IMG_Load(imagePath.c_str());
	if (!surface) {
		throw std::runtime_error("Failed to load image: " + imagePath);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	return texture;
}
