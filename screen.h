#pragma once
#include "SDL2.h"

class Screen {
public:
    virtual void init(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handleInput(SDL_Event& event) = 0;
};