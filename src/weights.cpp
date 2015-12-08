#include "weights.h"

weights::weights()
{
	c = 0.01;

	wnumPoints = 18.9237;
	wnumSegments = 3.58878;

	wnumSLGroups = 11.0525;
	wSLmax = 5.6717;
	wnumGroupsWLines = 6.5358;
	wnumNegativeSL = 6.03285;
	wnumPositiveSL = 11.673;

	wratioVH = 1.37;
	wratioVD = 0.975309;
	wratioHD = 1.02587;

	wmaxLength = 213.746;
	wminLength = 36.1282;
	waverageLength = 135.211;
	wmedianLength = 104.929;

	wnumAngleGroups = 6.77271;
	wnumObtuseAngles = 44.8471;
	wnumAcuteAngles = 32.546;
	wnumAngleGroupsWAngles = 4.35269;
	wnumLowAngles = 0.279092;
	waverageLowAngleLineLength = 48.5613;

	wBWratio = 278.302;
	wblackCounter = 782.157;
	wwhiteCounter = 109676;

	wcompositionPointDistances.push_back(101.957);
	wcompositionPointDistances.push_back(90.2972);
	wcompositionPointDistances.push_back(89.3982);
	wcompositionPointDistances.push_back(99.4577);
	wcompositionPointDistances.push_back(73.676);
	wcompositionPointDistances.push_back(57.6635);
	wcompositionPointDistances.push_back(56.3199);
	wcompositionPointDistances.push_back(70.2891);
	wcompositionPointDistances.push_back(58.6099);
	wcompositionPointDistances.push_back(37.5387);
	wcompositionPointDistances.push_back(36.3428);
	wcompositionPointDistances.push_back(53.1257);
	wcompositionPointDistances.push_back(65.5329);
	wcompositionPointDistances.push_back(46.5569);
	wcompositionPointDistances.push_back(45.3476);
	wcompositionPointDistances.push_back(61.1774);
}

weights::weights(vector<float> vals, vector<float> composition)
{
}

weights::~weights()
{
}

float weights::feedForward(float weightedVal, float value, int likeOrDislike)
{
	float newVal = 0; 

	float error = abs(weightedVal - value);

	error = error * c;

	if(likeOrDislike == 1)
	{
		if(value <= weightedVal)
		{
			newVal = weightedVal - error;
		}

		else
		{
			newVal = weightedVal + error;
		}
	}

	else
	{
		if(value <= weightedVal)
		{
			newVal = weightedVal + error;
		}
	
		else
		{
			newVal = weightedVal - error;
		}
	}

	return newVal;
}

void weights::activate()
{
}

void weights::train(vector<float> inputs, vector<float> compositionInput, int likeOrDislike)
{
		if(likeOrDislike == 1)
		{
			wnumPoints = feedForward(wnumPoints, inputs[0], 1);
			wnumSegments = feedForward(wnumSegments, inputs[1], 1);

			wnumSLGroups = feedForward(wnumSLGroups, inputs[2], 1);
			wSLmax = feedForward(wSLmax, inputs[3], 1);
			wnumGroupsWLines = feedForward(wnumGroupsWLines, inputs[4], 1);
			wnumNegativeSL = feedForward(wnumNegativeSL, inputs[5], 1);
			wnumPositiveSL = feedForward(wnumPositiveSL, inputs[6], 1);

			wratioVH = feedForward(wratioVH, inputs[7], 1);
			wratioVD = feedForward(wratioVD, inputs[8], 1);
			wratioHD = feedForward(wratioHD, inputs[9], 1);

			wmaxLength = feedForward(wmaxLength, inputs[10], 1);
			wminLength = feedForward(wminLength, inputs[11], 1);
			waverageLength= feedForward(waverageLength, inputs[12], 1);
			wmedianLength = feedForward(wmedianLength, inputs[13], 1);

			wnumAngleGroups = feedForward(wnumAngleGroups, inputs[14], 1);
			wnumObtuseAngles = feedForward(wnumObtuseAngles, inputs[15], 1);
			wnumAcuteAngles = feedForward(wnumAcuteAngles, inputs[16], 1);
			wnumAngleGroupsWAngles= feedForward(wnumAngleGroupsWAngles, inputs[17], 1);
			wnumLowAngles = feedForward(wnumLowAngles, inputs[18], 1);
			waverageLowAngleLineLength = feedForward(waverageLowAngleLineLength, inputs[19], 1);

			wBWratio = feedForward(wBWratio, inputs[20], 1);
			wblackCounter = feedForward(wblackCounter, inputs[21], 1);
			wwhiteCounter = feedForward(wwhiteCounter, inputs[22], 1);

			for(int i = 0; i<wcompositionPointDistances.size(); i++)
			{
				wcompositionPointDistances[i] = feedForward(wcompositionPointDistances[i], compositionInput[i], 1);
			}
		}

		/*
		else
		{
			wnumPoints = feedForward(wnumPoints, inputs[0], 0);
			wnumSegments = feedForward(wnumSegments, inputs[1], 0);

			wnumSLGroups = feedForward(wnumSLGroups, inputs[2], 0);
			wSLmax = feedForward(wSLmax, inputs[3], 0);
			wnumGroupsWLines = feedForward(wnumGroupsWLines, inputs[4], 0);
			wnumNegativeSL = feedForward(wnumNegativeSL, inputs[5], 0);
			wnumPositiveSL = feedForward(wnumPositiveSL, inputs[6], 0);

			wratioVH = feedForward(wratioVH, inputs[7], 0);
			wratioVD = feedForward(wratioVD, inputs[8], 0);
			wratioHD = feedForward(wratioHD, inputs[9], 0);

			wmaxLength = feedForward(wmaxLength, inputs[10], 0);
			wminLength = feedForward(wminLength, inputs[11], 0);
			waverageLength= feedForward(waverageLength, inputs[12], 0);
			wmedianLength = feedForward(wmedianLength, inputs[13], 0);

			wnumAngleGroups = feedForward(wnumAngleGroups, inputs[14], 0);
			wnumObtuseAngles = feedForward(wnumObtuseAngles, inputs[15], 0);
			wnumAcuteAngles = feedForward(wnumAcuteAngles, inputs[16], 0);
			wnumAngleGroupsWAngles= feedForward(wnumAngleGroupsWAngles, inputs[17], 0);
			wnumLowAngles = feedForward(wnumLowAngles, inputs[18], 0);
			waverageLowAngleLineLength = feedForward(waverageLowAngleLineLength, inputs[19], 0);

			wBWratio = feedForward(wBWratio, inputs[20], 0);
			wblackCounter = feedForward(wblackCounter, inputs[21], 0);
			wwhiteCounter = feedForward(wwhiteCounter, inputs[22], 0);

			for(int i = 0; i<wcompositionPointDistances.size(); i++)
			{
				wcompositionPointDistances[i] = feedForward(wcompositionPointDistances[i], compositionInput[i], 0);
			}
		}
		*/
}