#pragma once

#include "ofMain.h"
#include "lookieLines.h"

class slopeLineGroup{
public:
	//rethinking this slopeLineGrouping instead of making groups based on the lines
	//i think i will premake the groups and then put lines into them

	slopeLineGroup();
	slopeLineGroup(float min, float max, int n);
	~slopeLineGroup();

	int numLines;

	float minSlope;
	float maxSlope;

	vector<lookieLines> SLGlines;
};