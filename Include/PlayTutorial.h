#pragma once
#include <SDL.h>
#include <iostream>
#include "Song.h"
#include "NotesTracker.h"
#include "ScoreTracker.h"
#include "Tutorial.h"


bool loadSong(Tutorial* tutorial);

void startTutorial(Tutorial* tutorial, SDL_Renderer* renderer);

bool loadMapValues(Tutorial* tutorial);

bool loadScoreTracker(Tutorial* tutorial);

bool closeTutorial(Tutorial* tutorial);

bool queue(Tutorial* tutorial);


