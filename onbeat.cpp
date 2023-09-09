#include "onbeat.h"
#include "metronome.h"
#include "button.h"


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Mix_Music* tickSound = NULL;
Mix_Chunk* gpress = NULL;
//Key press surfaces constants


int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("something went wrong: %s\n",SDL_GetError());
	}
	else {
		printf("lets get started\n");
	}

	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 64) < 0) {
		printf("SDL_mixer bad: %s\n", Mix_GetError());
	}

	//Create Window
	SDL_Window* window = SDL_CreateWindow("OnBeat", 0, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	//Create Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("SDL_CreateRenderer error\n");
	}
	
	
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
	
	
	gpress = Mix_LoadWAV("sounds/drum_click.wav");
	Metronome m1(60);
	m1.sendMsg();
	int bpm = m1.trackBPM();
	m1.playMetronome(bpm, gpress);
	
	

	bool quit = false;
	SDL_Event event;
	int mouseX = 0;
	int	mouseY = 0;

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
		// Clear the renderer
		SDL_RenderClear(renderer);

		// Render the button
		button.render();

		// Present the renderer
		SDL_RenderPresent(renderer);
	}

	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}



