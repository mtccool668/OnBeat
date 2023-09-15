#pragma once
#include "graphics.h"
#include "ContentHandler.h"
#include "assets.h"

class MainMenu {

public:
    MainMenu(SDL_Renderer* renderer);
    void update();
    ButtonName getButton(int mouseX, int mouseY);
    void render(SDL_Renderer* renderer);
    screen getScreen();
    void reset();


private:
    SDL_Renderer* renderer;
	ButtonState buttonState;
	ButtonName buttonName;
    screen screenID;
    
    SDL_Rect srects[4];
    SDL_Rect drects[4];
    
};