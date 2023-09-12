#pragma once
#include "screen.h"

class ScreenManager
{
public:
	ScreenManager(SDL_Renderer* renderer);
    void pushScreen(std::shared_ptr<Screen> screen);
    void popScreen();
    void updateScreen();
    void renderScreen();
    void handleInput(SDL_Event& event);
    bool isEmpty() const;
    int getScreenID();

private:
    SDL_Renderer* renderer;
    std::stack<std::shared_ptr<Screen>> screenStack;
    
};

