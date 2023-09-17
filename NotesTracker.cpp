#include "NotesTracker.h"


NotesTracker::NotesTracker(Song* song) {
	currentSong = song;
	currentNote = NONE;
	syncValues = 0;
}
	
void NotesTracker::setNoteType(int noteCount, int measures) {
	int type = noteCount / measures;
	switch (type) {
	case 1:
		currentNote = WHOLE;
		break;
	case 2:
		currentNote = HALF;
		break;
	case 4:
		currentNote = QUARTER;
		break;
	case 8:
		currentNote = EIGHTH;
		break;
	case 16:
		currentNote = SIXTEENTH;
	}
}


Uint32 NotesTracker::callback(Uint32 interval, void* param) {
	NotesTracker* timer = static_cast<NotesTracker*>(param);
	return timer->sync(interval);
}

Uint32 NotesTracker::sync(Uint32 interval) {
	currentSong->mapValues.push_back((float)SDL_GetTicks());
	return interval;
}

void NotesTracker::setMeasureValues(Song* song) {
	int interval = 60000 / song->getSongBPM();
	if (currentNote == EIGHTH) {
		interval /= 2;
	}
	else if (currentNote == SIXTEENTH) {
		interval /= 4;
	}

	SDL_TimerID syncValues = SDL_AddTimer(interval, sync, NULL);
	

}


std::vector<float> NotesTracker::getMapValues() {
	return currentSong->mapValues;
}

