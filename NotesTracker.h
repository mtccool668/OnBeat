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

	NotesTracker(Song* song);
	void setNoteType(int noteCount, int measures);
	void setMeasureValues(Song* song);
	std::vector<float> getMapValues();


private:
	SDL_TimerID syncValues;
	static Uint32 sync(Uint32 interval, void *param);
	Uint32 sync(Uint32 interval);
	Note currentNote;
	Song* currentSong;
	

};

