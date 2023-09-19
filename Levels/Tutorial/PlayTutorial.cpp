#include "PlayTutorial.h"

Song* tutorialSong = new Song("Tutorial", 165);
NotesTracker* tracker = new NotesTracker(tutorialSong, 4);
ScoreTracker* scoreTracker = new ScoreTracker();


bool loadSong(Tutorial* tutorial) {
	bool success = true;
	return success;
}

bool loadMapValues(Tutorial* tutorial) {
	bool success = true;
	
	tracker->setNoteType(16, 4);
	
	int BPM = tutorialSong->getBPM();
	tracker->setInterval(BPM);
	
	int prevTime = SDL_GetTicks();
	tracker->syncValues(tracker->getInterval());

	return true;
}

bool loadScoreTracker(Tutorial* tutorial) {
	bool success = true;
	
	return success;
}

bool queue(Tutorial* tutorial) {
	SDL_Event event;
	bool success = false;
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			break;

		case SDL_KEYDOWN:
			success = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			success = true;
			break;
		}
	}

	return success;

}

void startTutorial(Tutorial* tutorial, SDL_Renderer* renderer) {

	std::vector<float> playerValues;

	if (!loadSong(tutorial)) {
		printf("can't load song\n");
	}
	if (!loadMapValues(tutorial)) {
		printf("can't load map values\n");
	}
	if (!loadScoreTracker(tutorial)) {
		printf("can't load score tracker\n");
	}
	std::vector<float> mapValues = tracker->getMapValues();
	for (float val : mapValues) {
		std::cout << val << ", " << "\n";
	}

	/////////////////
	bool finished = false;
	bool repeat = false;
	int rightClicks = 0;
	int leftClicks = 0;
	
	while (!finished) {
		SDL_Event event;
		//printf("event landed");
		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					break;
				}
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_j:
					if (rightClicks == 16) {
						rightClicks = 0;
						repeat = true;
					}
					printf("%f\n", (float)SDL_GetTicks());
					playerValues.push_back((float)SDL_GetTicks());
					rightClicks += 1;
					break;

				case SDLK_f:
					if (leftClicks == 16) {
						leftClicks = 0;
						repeat = true;
					}
					leftClicks += 1;
					break;
				}



			}
			

		}

	}
}
	



bool closeTutorial(Tutorial* tutorial) {
	bool success = true;
	delete tracker;
	delete tutorial;
	return success;
}
