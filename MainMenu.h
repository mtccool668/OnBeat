#pragma once
#include "screen.h"


class MainMenu : public Screen {

public:
    MainMenu(SDL_Renderer* renderer, const std::string& imgPath);
    void update() override;
    void render(SDL_Renderer* renderer) override;
    void handleInput(SDL_Event& event) override;
    int get() override;
    
    std::vector<SDL_Rect> loadButtons(const std::string imgPath, int width, int height);

private:
    SDL_Renderer* renderer;
    const std::string& imgPath;
    SDL_Texture* bkgTexture;
    int ID;
};