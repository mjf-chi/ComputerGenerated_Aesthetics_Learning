#pragma once

#include "ofMain.h"
#include <vector>

class lookie{
public:
	lookie();
	lookie(int uh);
	~lookie();

	void locationFind();
	void draw();

	int id;
	float fitnessVal;

	int numPoints;
	int numSegments;
	vector<int> numPointsPerSeg;

	vector<ofPoint> thePoints;
};