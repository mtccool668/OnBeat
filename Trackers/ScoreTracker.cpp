#include "ScoreTracker.h"

ScoreTracker::ScoreTracker() {
	acc = 0.0;
	UR = 0.0;
}


/*

Accuracy = [ 300(n of 300 hits) + 100(n of 100 hits) + 50(n of 50 hits) ] / 300(n of total hits)
UR (unstable rate) = standard deviation of hit errors (ms)

*/

void ScoreTracker::getHitValues(std::vector<float>& playerValues, std::vector<float>& mapValues) {
	for (int i = 0; i < playerValues.size(); i++) {
		float diff = abs(mapValues[i] - playerValues[i]);
		if (diff <= 20) {
			scoreValues.push_back(300);
		}
		else if (diff > 20 && diff <= 50) {
			scoreValues.push_back(100);
		}
		else if (diff > 50 && diff <= 100) {
			scoreValues.push_back(50);
		}
		else {
			//missed notes
			scoreValues.push_back(0);
		}
	}
}


float ScoreTracker::calculateAcc(std::vector<float>& scoreValues) {
	int count_300 = 0;
	int count_100 = 0;
	int count_50 = 0;
	int count_miss = 0;

	for (int i = 0; i < scoreValues.size(); ++i) {
		if (scoreValues[i] == 300) {
			count_300++;
		}
		else if (scoreValues[i] == 100) {
			count_100++;
		}
		else if (scoreValues[i] == 50) {
			count_50++;
		}
		else {
			count_miss++;
		}
	}

	acc = (float)(count_300 + count_100 + count_50) / (300 * (count_300 + count_100 + count_50 + count_miss));
	return acc;


}

float ScoreTracker::calculateUR(std::vector<float>& playerValues) {
	float sum = 0.0;
	int size = (int)playerValues.size();
	
	for (int i = 0; i < size; ++i) {
		sum += playerValues[i];
	}
	float mean = sum / size;
	float variance = 0.0;
	for (int i = 0; i < size; ++i) {
		variance += (float)pow(playerValues[i] - mean, 2);
	}
	variance /= size;

	UR = sqrt(variance);
	return UR;
}

ScoreTracker::~ScoreTracker() {

}
