#pragma once
#include "SDL2.h"

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

