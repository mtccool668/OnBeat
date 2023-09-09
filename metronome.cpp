#include "metronome.h"

void Metronome::sendMsg() {
	Metronome met(60);
	std::cout << met.ticks << "\n";
	std::cout << met.tempo << "\n";
}

Uint32 callback(Uint32 interval, void* param) {
	int* clickCount = (int*)param;
	printf("BPM: %d\n", *clickCount * 10);
	return 0;
}

float calculateBPM(int clickCount, float totalClickInterval) {
	if (clickCount < 2) {
		return 0.0f;
	}
	float averageClickInterval = totalClickInterval / (clickCount - 1);
	return 60000.0f / averageClickInterval;
}

int Metronome::trackBPM() {
	float BPM = 0.0;
	int clickCount = 0;
	Uint32 lastClickTime = 0;
	Uint32 startTime = 0;
	Uint32 currTime = 0;
	float totalClickInterval = 0.0f;
	const int MAX_CLICKS = 4;
	const Uint32 RESET_TIME = 10000;
	Uint32 lastResetTime = 0;


	SDL_Event event;
	bool runTimer = true;

	SDL_TimerID timerID = SDL_AddTimer(5000, callback, &clickCount);

	while (runTimer) {
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type) {
			case SDL_QUIT:
				runTimer = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (clickCount == 0 || (SDL_GetTicks() - lastResetTime) >= RESET_TIME) {
						totalClickInterval = 0.0f;
						clickCount = 0;
						lastResetTime = SDL_GetTicks();
						startTime = SDL_GetTicks();
					}
					if (clickCount > 0) {
						currTime = SDL_GetTicks();
						totalClickInterval += float(currTime - lastClickTime);
					}

					lastClickTime = SDL_GetTicks();
					clickCount++;

					BPM = calculateBPM(clickCount, totalClickInterval);

					printf("BPM: %.2f\n", BPM);
				}
				break;
			}
		}

	}
	return BPM;
}

void Metronome::playMetronome(int BPM, Mix_Chunk* tickSound) {
	const int BEAT_DURATION_MS = (60 * 1000) / BPM;
	std::cout << "Playing metronome..." << "\n";
	SDL_Delay(1500);
	while (1) {
		Mix_PlayChannel(-1, tickSound, 0);
		SDL_Delay(BEAT_DURATION_MS);
	}

}