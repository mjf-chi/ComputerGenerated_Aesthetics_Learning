#pragma once

#include "ofMain.h"

class intersectAngleGroup{
public:
	intersectAngleGroup();
	intersectAngleGroup(float min, float max);
	~intersectAngleGroup();

	//"IAG" = intersect angle group
	float IAGmin;
	float IAGmax;

	vector<float> anglesInIAG;
};