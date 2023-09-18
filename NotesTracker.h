#pragma once
#include "SDL2.h"
#include "Song.h"



class NotesTracker
{
public:

	enum Note {
		NONE,
		WHOLE,
		HALF,
		QUARTER,
		EIGHTH,
		SIXTEENTH
	};

	NotesTracker(Song* song, int tm);
	
	void setNoteType(int noteCount, int measures);
	
	void setInterval(int BPM);
	
	float getInterval();
	
	void syncValues(float interval);
	
	std::vector<float> getMapValues();


private:
	Note currentNote;
	Song* currentSong;
	float currentInterval;
	int totalMeasures;
	

};

