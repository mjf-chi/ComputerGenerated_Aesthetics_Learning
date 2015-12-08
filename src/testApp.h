#pragma once

#include "ofMain.h"
#include "lookie.h"
#include "weights.h"
#include "slopeLineGroup.h"
#include "lookieLines.h"
#include "intersectAngleGroup.h"
#include "specialPointClass.h"
#include <string>
#include <vector>

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void slopeAnalysis(lookie g);
		void angleAnalysis(lookie g);
		void horizontalVertical(vector<lookieLines> l);
		void lengthAnalysis(vector<lookieLines> l);
		void blackWhite();
		
		//"o" is for one "t" is for two
		float getDistance(ofPoint o, ofPoint t);

		void keyPressed(int key);
		
		lookie generated;

		int counter;

		bool firstTime;
		bool runGeneticSystem;

		vector<float> weightVals;
		vector<float> compositionVals;

		weights neuralWeightSystem;

		bool aestheticsGenetics;
		//genetics part
		int populationSize;
		bool firstGeneticsIteration;
		lookie bestLookie;
		lookie worstLookie;

		vector<lookie> badPop;
		vector<int> putridPool;
		vector<lookie> nastyChildren;

		vector<lookie> population;
		vector<int> matingPool;
		vector<lookie> children;

		void iniateGeneticSystem();
		void updateGeneticSystem();
		void fitnessTest(int ID);
		void weaknessTest(int ID);
		float findError(float input, float neuralWeightVal);
		lookie crossOver(lookie parentA, lookie parentB);

		float highestFitness;
		float currentHighFit;

		float lowestFitness;
		float currentLowFit;

		//saving best image to imagefile
		ofImage leastFit;
		ofFbo fbo2;
		ofPixels pix2;

		ofImage mostFit;
		ofFbo fbo;
		ofPixels pix;

		int imageCounter;
};
