#include "NotesTracker.h"


NotesTracker::NotesTracker(Song* song, int tm) {
	currentSong = song;
	currentNote = NONE;
	currentInterval = 0;
	totalMeasures = tm;
}
	
void NotesTracker::setNoteType(int noteCount, int totalMeasures) {
	int type = noteCount / totalMeasures;
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




void NotesTracker::setInterval(int BPM) {
	float interval = 60000 / (float)BPM;
	if (currentNote == EIGHTH) {
		interval /= 2;
	}
	else if (currentNote == SIXTEENTH) {
		interval /= 4;
	}
	
	currentInterval = interval;
	

}

void NotesTracker::syncValues(float interval) {
	printf("%f\n", interval);
	int prevTime = SDL_GetTicks();
	int currTime = 0;
	for (int i = 0; i < totalMeasures * 4; i++) {
		currTime = SDL_GetTicks();
		currentSong->mapValues.push_back((float)interval);
	}
}


std::vector<float> NotesTracker::getMapValues() {
	return currentSong->mapValues;
}

float NotesTracker::getInterval() {
	return currentInterval;
}

