#include "Song.h"

Song::Song(const char* name, int bpm){
	
	songName = name;
	BPM = bpm;


}

const char* Song::getName() {
	return songName;
}

int Song::getBPM() {
	return BPM;
}