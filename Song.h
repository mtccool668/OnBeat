#pragma once
#include "SDL2.h"

class Song
{
public:
	Song(const char* name);
	const char* getSongName();
	int getSongBPM();

	std::vector<float> mapValues;
	

private:
	int BPM;
	const char* songName;
};

