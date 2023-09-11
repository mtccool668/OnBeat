#include "VideoPlayer.h"
#include "SDL2.h"
#include <vector>
#include <filesystem>
#include "GameLogic.h"

VideoPlayer::VideoPlayer(SDL_Renderer* renderer, const std::string& folderPath) : renderer(renderer), folderPath(folderPath){
	if (!renderer) {
		printf("video player cannot start");
	}
	if (folderPath.empty() || !std::filesystem::is_directory(folderPath)) {
		printf("can't find folder path");

	}
}

void VideoPlayer::playVideo(SDL_Renderer* renderer, const std::string& folderPath, int targetFrameRate) {
	//Load video frames
	int frameCount = countFolderContents("videos/rick_frames");;

	std::vector<SDL_Surface*> loadingFrames(frameCount);
	std::vector<SDL_Texture*> frameTextures(frameCount);
	std::vector<std::string> frameFileNames(frameCount);

	for (int i = 0; i < frameCount; i++) {
		frameFileNames[i] = folderPath + "/frame (" + std::to_string(i + 1) + ").bmp";
		std::cout << frameFileNames[i] << "\n";
		loadingFrames[i] = IMG_Load(frameFileNames[i].c_str());
		if (!loadingFrames[i]) {
			printf("something went wrong with the frames, can't play video :(\n");
		}
		frameTextures[i] = SDL_CreateTextureFromSurface(renderer, loadingFrames[i]);
		if (!frameTextures[i]) {
			return;
		}
	}
	//set game flag 
	bool playingVideo = true;

	printf("I got to %d frames\n", frameCount);

	//Playing video
	int frameTime = 1000 / targetFrameRate;

	for (int i = 0; i < frameCount; i++) {
		discardAllEvents(playingVideo);

		Uint32 frameStartTime = SDL_GetTicks();

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, frameTextures[i], NULL, NULL);
		SDL_RenderPresent(renderer);

		auto frameEndTime = SDL_GetTicks();
		auto frameDuration = frameEndTime - frameStartTime;

		if (frameDuration < frameTime) {
			SDL_Delay(frameTime - frameDuration);
		}

		SDL_FreeSurface(loadingFrames[i]);
		SDL_DestroyTexture(frameTextures[i]);

	}
}
