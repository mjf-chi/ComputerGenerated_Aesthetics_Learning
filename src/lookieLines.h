#pragma once

#include "ofMain.h"

class lookieLines{
public:
	lookieLines();

	//"f" = first point "s" = second point
	lookieLines(ofPoint f, ofPoint s);
	~lookieLines();

	bool vertical;
	bool negativeS;
	float slope;
	ofPoint a;
	ofPoint b;

	float length;
};