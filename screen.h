#pragma once
#include "SDL2.h"

class Screen {
public:
    Screen(SDL_Renderer* renderer, const std::string& imgPath);
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handleInput(SDL_Event& event) = 0;
    virtual int get();
    
 
private:
    SDL_Renderer* renderer;
    const std::string& imgPath;
    SDL_Texture* bkgTexture;
    int ID;
};