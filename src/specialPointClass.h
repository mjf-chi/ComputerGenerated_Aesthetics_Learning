#pragma once

#include "ofMain.h"

class specialPointClass{
public:
	specialPointClass();
	specialPointClass(int xLocation, int yLocation);
	~specialPointClass();

	void drawDot();

	int xLoc;
	int yLoc;
	float totalDistance;
	float averageDistance;
};