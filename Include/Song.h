#pragma once
#include <SDL.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>

class Song
{
public:
	Song(const char* name, int BPM);
	const char* getName();
	int getBPM();

	std::vector<float> mapValues;
	

private:
	int BPM;
	const char* songName;
};

