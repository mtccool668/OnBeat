#include "Song.h"

Song::Song(const char* name) {
	
	songName = name;
	BPM = 0;


}

const char* Song::getSongName() {
	return songName;
}

int Song::getSongBPM() {
	return BPM;
}