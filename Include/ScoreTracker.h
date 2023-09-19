#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
class ScoreTracker
{

public:
	ScoreTracker();
	~ScoreTracker();

	void getHitValues(std::vector<float>& playerValues, std::vector<float>& mapValues);
	float calculateAcc(std::vector<float>& playerValues);
	float calculateUR(std::vector<float>& playerValues);
	


private:
	
	std::vector<int> scoreValues;
	float UR;
	float acc;

	
};

