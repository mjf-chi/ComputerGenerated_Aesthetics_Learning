#pragma once

#include "ofMain.h"
#include <vector>
#include "lookie.h"

class weights{
public:
	weights();
	weights(vector<float> vals, vector<float> composition);
	~weights();

	float feedForward(float weightedVal, float value, int likeOrDislike);
	void activate();
	void train(vector<float> inputs, vector<float> compositionInput, int likeOrDislike);

	//adding "w" to start because there are classes that have
	//these names already and these are the neural weights that 
	//later get adjusted in order to find the ideal number

	float c;

	//lookie class variables
	float wnumSegments;
	float wnumPoints;
	
	//SL = slope line
	float wnumSLGroups;
	float wSLmax;
	float wnumGroupsWLines;
	float wnumNegativeSL;
	float wnumPositiveSL;

	//angle class variables
	float wnumAngleGroups;
	float wnumObtuseAngles;
	float wnumAcuteAngles;
	float wnumAngleGroupsWAngles;
	float wnumLowAngles;
	float waverageLowAngleLineLength;

	//horizontal, vertical, diagonal ratios
	float wratioVH;
	float wratioVD;
	float wratioHD;

	//length analysis variables
	float wminLength;
	float wmaxLength;
	float waverageLength;
	float wmedianLength;

	//black and white analysis variables
	vector<float> wcompositionPointDistances;
	float wBWratio;
	float wblackCounter;
	float wwhiteCounter;

};