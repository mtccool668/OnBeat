#pragma once
#include <SDL.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>


enum ButtonState {
	NORMAL,
	HOVER,
	PRESS
};

enum ButtonName {
	NONE,
	PLAY,
	EXIT,
	SETTINGS,
	SHOP,
	PROFILE,
	PHONE
};

//Textures
extern SDL_Texture* entityTextures[4];
extern SDL_Texture* bkgTextures[4];
extern SDL_Texture* characterTextures[4];
extern SDL_Texture* buttonTextures[4];
extern SDL_Texture* fontTextures[4];

//Animations
extern int clips300_frame;
extern SDL_Rect clips300[4];
