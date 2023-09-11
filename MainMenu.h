#pragma once
#include "screen.h"

class MainMenuScreen : public Screen {
public:
    void init(SDL_Renderer* renderer) override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
    void handleInput(SDL_Event& event) override;
};