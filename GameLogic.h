#pragma once
#include "SDL2.h"
#include "graphics.h"


void startGame(SDL_Window* window, SDL_Renderer* renderer);

void endGame(SDL_Window* window, SDL_Renderer* renderer);

SDL_Window* getWindow();

SDL_Renderer* getRenderer();

void discardAllEvents(bool quit);

int countFolderContents(const std::string& folderPath);



