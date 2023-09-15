#pragma once
#include "SDL2.h"
#include "ContentHandler.h"
#include "tools.h"


void render300(SDL_Renderer* renderer, SDL_Texture* textures[], int textureID, int width, int height, 
	int rows, int cols, int frameCount, int targetFrameRate);


