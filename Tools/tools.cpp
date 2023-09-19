#include "tools.h"

void discardAllEvents(bool quit) {
	SDL_Event event;
	while (!quit) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				SDL_Quit();
				break;
			}
		}
	}
}
int countFolderContents(const std::string& folderPath) {
	namespace fs = std::filesystem;
	try {
		int count = 0;
		for (const auto& entry : fs::directory_iterator(folderPath)) {
			count++;
		}
		return count;
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1; // Return a negative value to indicate an error
	}
}