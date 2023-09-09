#pragma once
#include "onbeat.h"



class Metronome
{
public:
	int ticks;
	std::string tempo;
	

	Metronome(int t) {
		ticks = t;
		tempo = "Trying to create metronome...";
	}
	

	void sendMsg();
	int trackBPM();
	void playMetronome(int n, Mix_Chunk* c);
	
	
};

