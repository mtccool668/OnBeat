#pragma once
#include "SDL2.h"
class VideoPlayer
{
public:
	
	VideoPlayer(SDL_Renderer* renderer, const std::string& folderPath);
	void playVideo(SDL_Renderer* renderer, const std::string& folderPath, int targetFrameRate);

private:
	const std::string& folderPath;
	SDL_Renderer* renderer;
};

