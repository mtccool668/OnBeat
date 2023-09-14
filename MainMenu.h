#pragma once
#include "button.h"
#include "graphics.h"
#include "gamelogic.h"

class MainMenu {

public:
    MainMenu(SDL_Renderer* renderer, const std::string& bkgPath, const std::string& titlePath);
    void update();
    ButtonName getButton(int mouseX, int mouseY);
    void render(SDL_Renderer* renderer);
    screen get();
    void reset();

    
    void loadTextures(SDL_Renderer* renderer, const std::string imgPath, int width, int height);

private:
    SDL_Renderer* renderer;
    const std::string& bkgPath;
    const std::string& titlePath;
    SDL_Texture* bkgTexture;
    SDL_Texture* titleTexture;
    SDL_Texture* sheet;

    std::vector<SDL_Rect> srects;
    SDL_Rect drects[4];
    ButtonState buttonState;
    ButtonName buttonName;
    
};