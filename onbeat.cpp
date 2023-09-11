#include "SDL2.h"
#include "metronome.h"
#include "button.h"
#include "screen.h"
#include "ScreenManager.h"
#include "MainMenu.h"
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <thread>

//Key press surfaces constants
struct GameSystems {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

int countFolderContents(const std::string& folderPath) {
	namespace fs = std::filesystem;
	try {
		int count = 0;
		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			count++;
		}
		return count;
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1; // Return a negative value to indicate an error
	}
}

void playVideo(SDL_Renderer* renderer, const std::string& folderPath, int frameCount, int targetFrameRate) {
	std::vector<SDL_Surface*> loadingFrames(frameCount);
	std::vector<SDL_Texture*> frameTextures(frameCount);
	std::vector<std::string> frameFileNames(frameCount);

	for (int i = 0; i < frameCount; i++) {
		frameFileNames[i] = folderPath + "/frame (" + std::to_string(i + 1) + ").bmp";
		std::cout << frameFileNames[i] << "\n";
		loadingFrames[i] = IMG_Load(frameFileNames[i].c_str());
		if (!loadingFrames[i]) {
			printf("something went wrong with the frames");
		}
		frameTextures[i] = SDL_CreateTextureFromSurface(renderer, loadingFrames[i]);
		if (!frameTextures[i]) {
			return;
		}
	}

	int frameTime = 1000 / targetFrameRate;

	for (int i = 0; i < frameCount; i++) {
		Uint32 frameStartTime = SDL_GetTicks();

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, frameTextures[i], NULL, NULL);
		SDL_RenderPresent(renderer);

		auto frameEndTime = SDL_GetTicks();
		auto frameDuration = frameEndTime - frameStartTime;

		if (frameDuration < frameTime) {
			SDL_Delay(frameTime - frameDuration);
		}

	}

	for (int i = 0; i < frameCount; i++) {
		SDL_FreeSurface(loadingFrames[i]);
		SDL_DestroyTexture(frameTextures[i]);
	}
}


int main(int argc, char* argv[]) {

	int frameCount = countFolderContents("videos/rick_frames");
	int targetFrameRate = 25;
	printf("I got to %d frames\n", frameCount);
	bool ignoreEvents = true;
	std::thread videoThread(playVideo, renderer, "videos/rick_frames", frameCount, targetFrameRate);



	ScreenManager screenManager(renderer);
	std::unique_ptr<Screen> loadingScreen = std::make_unique<MainMenu>();
	screenManager.pushScreen(std::move(loadingScreen));



	//Load Button Images
	SDL_Texture* buttonDefaultTexture = IMG_LoadTexture(renderer, "images/left.bmp");
	SDL_Texture* buttonHoverTexture = IMG_LoadTexture(renderer, "images/right.bmp");
	if (!buttonDefaultTexture || !buttonHoverTexture) {
		printf("Failed to load button textures.\n");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create Button
	Button button(renderer, buttonDefaultTexture, buttonHoverTexture, 100, 100, 200, 100);


	/*gpress = Mix_LoadWAV("sounds/niga.wav");
	Metronome m1(60);
	m1.sendMsg();
	int bpm = m1.trackBPM();
	m1.playMetronome(bpm, gpress);
	*/



	bool quit = false;
	SDL_Event event;
	int mouseX = 0;
	int	mouseY = 0;

	videoThread.join();
	while (!quit) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_MOUSEMOTION:
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				button.handleMouseHover(mouseX, mouseY);
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					mouseX = event.button.x;
					mouseY = event.button.y;
					if (button.isClicked(mouseX, mouseY)) {
						printf("Button clicked!\n");
					}
				}
				break;
			}
		}
		screenManager.update();
		screenManager.render();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}