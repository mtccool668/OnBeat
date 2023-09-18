#include "playTutorial.h"

Song* tutorial = new Song("Tutorial", 165);
NotesTracker* tracker = new NotesTracker(tutorial, 4);

bool loadSong() {
	bool success = true;
	return success;
}

bool loadMapValues() {
	bool success = true;
	
	tracker->setNoteType(16, 4);
	
	int BPM = tutorial->getBPM();
	tracker->setInterval(BPM);
	
	int prevTime = SDL_GetTicks();
	tracker->syncValues(tracker->getInterval());

	return true;
}

bool loadScoreTracker() {
	bool success = true;
	
	return success;
}

void playTutorial() {

	if (!loadSong()) {
		printf("can't load song\n");
	}
	if (!loadMapValues()) {
		printf("can't load map values\n");
	}
	if (!loadScoreTracker()) {
		printf("can't load score tracker\n");
	}
	std::vector<float> mapValues = tracker->getMapValues();
	for (float val : mapValues) {
		std::cout << val << ", " << "\n";
	}
}


bool closeTutorial(Song* song) {
	bool success = true;
	delete tracker;
	delete tutorial;
	return success;
}
