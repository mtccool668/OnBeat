#include "VideoPlayer.h"
#include "SDL2.h"

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