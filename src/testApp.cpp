#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableAlphaBlending();
	neuralWeightSystem = weights();

	ofBackground(255);
	bestLookie = lookie();
	worstLookie = lookie();
	populationSize = 0;
	highestFitness = 0;
	lowestFitness = 7400;

	firstTime = true;
	firstGeneticsIteration = true;
	aestheticsGenetics = true;

	fbo.allocate(ofGetWidth(), ofGetHeight());
	pix.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	mostFit.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);

	fbo2.allocate(ofGetWidth(), ofGetHeight());
	pix2.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	leastFit.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);

	imageCounter = 0;

	int whichProgramToRunFirst = 0;
	cout << "Run Aesthetic weighting first or Genetic Image Creation?" << endl;
	cout << "Enter a number greater than 1 for Genetic Image Creation." << endl;
	cout << "Enter a number less than one for Aesthetic Weight Program." << endl;

	cin >> whichProgramToRunFirst;

	if(whichProgramToRunFirst > 1)
	{
		aestheticsGenetics = false;
		iniateGeneticSystem();
		firstGeneticsIteration = false;
	}

	cout << "SETUP COMPLETE" << endl;
}

//--------------------------------------------------------------
void testApp::update(){
	if(aestheticsGenetics)
	{
		if(!firstTime)
		{
			cout << "NUMPOINTS: " << neuralWeightSystem.wnumPoints << endl;
			cout << "NUMSEGMENTS: " << neuralWeightSystem.wnumSegments << endl;

			cout << "NUMSLGroups: " << neuralWeightSystem.wnumSLGroups << endl;
			cout << "SLmax: " << neuralWeightSystem.wSLmax << endl;
			cout << "NUMGROUPSWLINES: " << neuralWeightSystem.wnumGroupsWLines << endl;
			cout << "NUMNEGATIVESL: " << neuralWeightSystem.wnumNegativeSL << endl;
			cout << "NUMPOSITIVESL: " << neuralWeightSystem.wnumPositiveSL << endl;

			cout << "RATIOVH: " << neuralWeightSystem.wratioVH << endl;
			cout << "RATIOVD: " << neuralWeightSystem.wratioVD << endl;
			cout << "RATIOHD: " << neuralWeightSystem.wratioHD << endl;

			cout << "MAXLENGTH: " << neuralWeightSystem.wmaxLength << endl;
			cout << "MINLENGTH: " << neuralWeightSystem.wminLength << endl;
			cout << "AVERAGELENGTH: " << neuralWeightSystem.waverageLength << endl;
			cout << "MEDIANLENGTH" << neuralWeightSystem.wmedianLength << endl;

			cout << "NUMANGLEGROUPS: " << neuralWeightSystem.wnumAngleGroups << endl;
			cout << "NUMOBTUSEANGLES: " << neuralWeightSystem.wnumObtuseAngles << endl;
			cout << "NUMACUTEANGLES: " << neuralWeightSystem.wnumAcuteAngles << endl;
			cout << "NUMANGLEGROUPSWANGLES: " << neuralWeightSystem.wnumAngleGroupsWAngles << endl;
			cout << "NUMLOWANGLES: " << neuralWeightSystem.wnumLowAngles << endl;
			cout << "AVERAGELOWANGLESLINELENGTH: " << neuralWeightSystem.waverageLowAngleLineLength << endl;

			cout << "BWRATIO: " << neuralWeightSystem.wBWratio << endl;
			cout << "BLACKCOUNTER: " << neuralWeightSystem.wblackCounter << endl;
			cout << "WHITECOUNTER: " << neuralWeightSystem.wwhiteCounter << endl;

			for(int i = 0; i<16; i++)
			{
				cout << "AVERAGEDISTANCE " << i << ": " << neuralWeightSystem.wcompositionPointDistances[i] << endl;
			}

			int likeDislike = 0;
			cin >> likeDislike;

			if(likeDislike == 8)
			{
				aestheticsGenetics = false;
			}

			neuralWeightSystem.train(weightVals, compositionVals, likeDislike);
			weightVals.clear();
			compositionVals.clear();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	if(aestheticsGenetics)
	{
		generated = lookie();
		generated.locationFind();
		generated.draw();

		//cout << "Number of Points: " << generated.numPoints << endl;
		weightVals.push_back(generated.numPoints); //0
		//cout << "Number of Segments: " << generated.numSegments << endl;
		weightVals.push_back(generated.numSegments); //1

		slopeAnalysis(generated);
		angleAnalysis(generated);
		blackWhite();

		firstTime = false;
	}

	else
	{
		if(firstGeneticsIteration)
		{
			cout << "First Genetics Iteration" << endl;

			iniateGeneticSystem();
			firstGeneticsIteration = false;
		}
		
		for(int i = 0; i< population.size(); i++)
		{
			cout << "drawing population" << endl;
			population[i].draw();

			cout << "Draw complete" << endl;

			fitnessTest(i);
			ofClear(255, 255, 255);
		}

		for(int i = 0; i<badPop.size(); i++)
		{
			cout << "onto bad population" << endl;
			badPop[i].draw();
			weaknessTest(i);
			ofClear(255, 255, 255);
		}

		updateGeneticSystem();

		cout << "Continue Genetics or go to aesthetics?" << endl;
		cout << "Enter a number less than or equal to 1 to continue genetics" << endl;
		int decisionMaking = 0;
		//cin >> decisionMaking;
		decisionMaking = 1;

		if(decisionMaking > 1)
		{
			aestheticsGenetics = true;
		}

		bestLookie.draw();

		/*	
		ofSaveImage(pix, bestLookingString, OF_IMAGE_QUALITY_MEDIUM);
		cout << "Image Saved as " << bestLookingString << endl;
		imageCounter++;
		*/
		//fbo.begin();
		//fbo.readToPixels(pix);
		//glReadPixels(0, 0, ofGetWidth(), ofGetHeight(), GL_RGB, GL_UNSIGNED_BYTE, pix.getPixels());
		//ofImage imageFromBest = ofImage(pix);

		mostFit.grabScreen(0,0, ofGetWidth(), ofGetHeight());

		std::string bestLookingString = "bestLooking";
		bestLookingString += std::to_string(imageCounter);
		bestLookingString += ".jpg";

		cout << "Saving Image " << endl;
		mostFit.saveImage(bestLookingString, OF_IMAGE_QUALITY_HIGH);
		cout << "Image Saved as " << bestLookingString << endl;
		//cout << pix.size() << endl;
		//ofSaveImage(pix, bestLookingString, OF_IMAGE_QUALITY_MEDIUM);
		//fbo.end();

		worstLookie.draw();

		leastFit.grabScreen(0,0, ofGetWidth(), ofGetHeight());

		std::string worstLookingString = "worstLooking";
		worstLookingString += std::to_string(imageCounter);
		worstLookingString += ".jpg";

		cout << " Saving Image " << endl;
		leastFit.saveImage(worstLookingString, OF_IMAGE_QUALITY_HIGH);
		cout << "Image Saved as " << worstLookingString << endl;
		

		imageCounter++;
	}
}

void testApp::slopeAnalysis(lookie g)
{
	cout << "RUNNING SLOPE ANALYSIS" << endl;
	vector<lookieLines> lines;

	int pointCounter = 1;
	//each "lookie" image may have several segments made up of multiple points
	//if there are two points that are not a part of the same segment then there
	//will be no line drawn. i do not want the lines between these points to be 
	//included in my analysis of the image
	//cout << "POINT COUNTER ESTABLISHED" << endl;

	for(int i = 0; i<g.numSegments; i++)
	{
		//cout << "INSIDE SEGMENT LOOP I: " << i << endl;

		for(int j = 0; j<g.numPointsPerSeg[i]; j++)
		{
			//cout << "NUMBER OF POINTS IN SEGMENT J: " << g.numPointsPerSeg[i] << endl;
			//cout << "INSIDE POINTS PER SEGMENT LOOP J: " << j << endl;
			//cout << "TOTAL POINTS: " << g.thePoints.size() << endl;
			//cout << "POINT COUNTER: " << pointCounter << endl;

			//stops trying to make a line once pointCounter reaches g.thePoints.size()-1
			if(pointCounter < g.thePoints.size())
			{
			lookieLines thisLine = lookieLines(g.thePoints[pointCounter-1], g.thePoints[pointCounter]);
			lines.push_back(thisLine);
			pointCounter++;

			//cout << "LINE PUT INTO VECTOR" << endl;
			}
		}
		//i add one to the point counter here because i want to skip making a line
		//(e.g. let's say point 10 and point 11 are parts of different segments. we don't
		//want to include a "lookieLines" of these two points. so once we have a point 9 
		//to point 10 line we want our next point to be a point 11 to point 12 line. this
		// means we have to get the point counter to 12, skipping from 10 to 12 :)
		pointCounter++;
		
		//cout << "COMPLETE SEGMENT" << endl;
	}

	//cout << "NUMBER OF LINES : " << lines.size() << endl;

	//this vector will hold all the groups of lines within a particular range of slopes
	//the number of these groups will have a weight as well as how wide the range is and
	//number of lines within a group

	vector<slopeLineGroup> SLgroups;

	float max = ofRandom(1, 10);

	float prevMax = 10000;
	float prevMin = max;

	int numGroups = int(ofRandom(4, 8));

	//cout << "Should be numGroups: " << numGroups << endl;

	for(int i = 0; i<numGroups-1; i++)
	{
		slopeLineGroup pnewGroup = slopeLineGroup(prevMin, prevMax, 1);
		slopeLineGroup nnewGroup = slopeLineGroup(prevMin, prevMax, -1);

		SLgroups.push_back(pnewGroup);
		SLgroups.push_back(nnewGroup);

		prevMax = prevMin;
		prevMin = prevMax/2;
	}

	SLgroups.push_back(slopeLineGroup(0, prevMax, 1));
	SLgroups.push_back(slopeLineGroup(0, prevMax, -1));

	//cout << "Number of Groups: " << SLgroups.size() << endl;
	weightVals.push_back(SLgroups.size());
	weightVals.push_back(max);
	
	int numNegativeSL = 0;
	int numPositiveSL = 0;

	for(int i = 0; i<lines.size(); i++)
	{
		for(int j = 0; j<SLgroups.size(); j++)
		{
			if(lines[i].negativeS)
			{
				if(lines[i].slope <= SLgroups[j].minSlope && lines[i].slope > SLgroups[j].maxSlope)
				{
					SLgroups[j].SLGlines.push_back(lines[i]);
					numNegativeSL++;
					break;
				}
			}

			else
			{
				if(lines[i].slope >= SLgroups[j].minSlope && lines[i].slope < SLgroups[j].maxSlope)
				{
					SLgroups[j].SLGlines.push_back(lines[i]);
					numPositiveSL++;
					break;
				}
			}
		}
	}

	int numGroupsWLines = 0;

	for(int i = 0; i<SLgroups.size(); i++)
	{
		//cout << "Number of lines in group " << i << " : " << SLgroups[i].SLGlines.size() << endl;
		
		if(SLgroups[i].SLGlines.size() > 0)
		{
			numGroupsWLines++;
		}
	}
	
	weightVals.push_back(numGroupsWLines);
	weightVals.push_back(numNegativeSL);
	weightVals.push_back(numPositiveSL);

	//cout << "There are " << numPositiveSL << " lines with positive slopes" << endl;
	//cout << "There are " << numNegativeSL << " lines with negative slopes" << endl;

	cout << "COMPLETE SLOPE ANALYSIS" << endl;

	horizontalVertical(lines);
	lengthAnalysis(lines);
}

	//now i have to analyze the angles made at all the points. i'll have to get all the points
	//within a segment. make a polyLine from that segment, and then use getAngleAtIndex to get
	//all the angles
void testApp::angleAnalysis(lookie g)
{
	int pointCounter = 0;

	vector<ofPolyline> polyLines;

	for(int i = 0; i<g.numSegments; i++)
	{
		ofPolyline newPolyline;

		for(int j = 0; j<g.numPointsPerSeg[i]; j++)
		{
			newPolyline.addVertex(g.thePoints[pointCounter]);
			pointCounter++;
		}

		polyLines.push_back(newPolyline);
	}

	//cout << "Number of Polylines: " << polyLines.size() << endl;

	vector<float> angles;

	float averageLowAngleLength = 0;
	int numLowAngles = 0;

	for(int i = 0; i<polyLines.size(); i++)
	{
		for(int j = 0; j<polyLines[i].size(); j++)
		{
			angles.push_back(polyLines[i].getAngleAtIndex(j));

			//okay, so what am I doing in these next few lines. Well, I decided that I
			//liked when low angles were made at the convergence of two long lines. So
			//here I am using the angle of 10 as my limit and finding the lengths of the
			//lines that form that angle
			if(polyLines[i].getAngleAtIndex(j) < 10)
			{
				//i don't want to use j-1 if j = 0 because i will most certainly get a some sort
				//of null pointer exception or something bad will happen. so if "j" does not = 0 
				//then I get to use my fun function, getting the index at "j-1". If "j" does = 0
				//then I have to find the distance between "j" being the first index of the 
				//polyline and the very last vertex in the polyline which is the number of vertices
				//inside the polyline - 1 because indexes start at zero whilst the size starts at 1
				if(j != 0)
				{
					//instead of making another array of lines i decided to use the polyLines that I already
					//had making the segments, then i sent two of the three vertices that make up an angle to
					//my distance function which returns a float.
					float lineOneLength = getDistance(polyLines[i].getVertices().at(j-1), polyLines[i].getVertices().at(j));
					averageLowAngleLength += lineOneLength;
				}

				else
				{
					float lineOneLength = getDistance(polyLines[i].getVertices().at(polyLines[i].getVertices().size()-1), polyLines[i].getVertices().at(j));
					averageLowAngleLength += lineOneLength;
				}

				if(j+1)
				{
					float lineTwoLength = getDistance(polyLines[i].getVertices().at(j), polyLines[i].getVertices().at(j+1));
					averageLowAngleLength += lineTwoLength;
				}
				else
				{
					float lineTwoLength = getDistance(polyLines[i].getVertices().at(j), polyLines[i].getVertices().at(0));
					averageLowAngleLength += lineTwoLength;
				}

				numLowAngles++;
			}
		}
	}

	//dividing by 2*numLowAngles because there are two lines per angle
	//so for every addition to the numLowAngles variable I added twice
	//to the averageLowAngleLength variable
	if(numLowAngles!=0)
	{
		averageLowAngleLength = averageLowAngleLength/(2*numLowAngles);
	}

	//cout << "Number of Low Angles: " << numLowAngles << endl;
	//cout << "Average Length of Low Angle Lines: " << averageLowAngleLength << endl;

	//cout << "Number of Angles: " << angles.size() << endl;

	int numAngleGroups = int(ofRandom(4, 10));
	weightVals.push_back(numAngleGroups);

	float angleRange = 180/numAngleGroups;

	float prevMin = 0;
	float prevMax = angleRange;

	//cout << "Angle Range: " << angleRange << endl;

	vector<intersectAngleGroup> IAGs;

	for(int i = 0; i<numAngleGroups; i++)
	{
		IAGs.push_back(intersectAngleGroup(prevMin, prevMax));

		prevMin = prevMax;
		prevMax = prevMin + angleRange;
	}

	int numObtuseAngles = 0;
	int numAcuteAngles = 0;

	for(int i = 0; i<angles.size(); i++)
	{
		for(int j = 0; j<IAGs.size(); j++)
		{
			if(angles[i] <= 90)
			{
				numAcuteAngles++;
			}
			else
			{
				numObtuseAngles++;
			}

			if(angles[i] >= IAGs[j].IAGmin && angles[i] < IAGs[j].IAGmax)
			{
				IAGs[j].anglesInIAG.push_back(angles[i]);
				break;
			}
		}
	}
	
	cout << "ACUTE: " << numAcuteAngles << endl;
	cout << "Obtuse: " << numObtuseAngles << endl;
	weightVals.push_back(numObtuseAngles);
	weightVals.push_back(numAcuteAngles);

	int numAngleGroupsWAngles = 0;

	for(int i = 0; i<IAGs.size(); i++)
	{
		if(IAGs[i].anglesInIAG.size() > 0)
		{
			numAngleGroupsWAngles++;
		}

		//cout << "Number of Angles in Group " << i << ": " << IAGs[i].anglesInIAG.size() << endl;
	}

	weightVals.push_back(numAngleGroupsWAngles);
	weightVals.push_back(numLowAngles);
	weightVals.push_back(averageLowAngleLength);

	cout << "ANGLE ANALYSIS COMPLETE" << endl;

}

float testApp::getDistance(ofPoint o, ofPoint t)
{
	float distance;

	distance = float(sqrt(pow((o.x-t.x), 2.0) + pow((o.y-t.y), 2.0)));

	return distance;
}

void testApp::horizontalVertical(vector<lookieLines> l)
{
	cout << "RUNNING HVD RATIO ANALYSIS" << endl;

	int numVertical = 0;
	int numHorizontal = 0;
	int numDiagonal = 0;

	for(int i = 0; i<l.size();i++)
	{
		if(l[i].vertical)
		{
			numVertical++;
		}
		
		else
		{
			if(abs(l[i].slope) > 2)
			{
				numVertical++;
			}

			else if(abs(l[i].slope) <= 2 && abs(l[i].slope) >= 0.5)
			{
				numDiagonal++;
			}

			else if(abs(l[i].slope) >= 0 && abs(l[i].slope) < 0.5)
			{
				numHorizontal++;
			}
		}
	}

	//cout << "Number of Diagonal: " << numDiagonal << endl;
	//cout << "Number of Horizontal: " << numHorizontal << endl;
	//cout << "Number of Vertical: " << numVertical << endl;

	float ratioVH = float(numVertical)/float(numHorizontal);
	float ratioVD = float(numVertical)/float(numDiagonal);
	float ratioHD = float(numHorizontal)/float(numDiagonal);

	//cout << "Vertical Horizontal Ratio: " << ratioVH << endl;
	weightVals.push_back(ratioVH);
	//cout << "Vertical Diagonal Ratio: " << ratioVD << endl;
	weightVals.push_back(ratioVD);
	//cout << "Horizontal Diagonal Ratio: " << ratioHD << endl;
	weightVals.push_back(ratioHD);

	cout << "COMPLETED HVD ANALYSIS" << endl;
}

void testApp::lengthAnalysis(vector<lookieLines> l)
{

	cout << "RUNNING LENGTH ANALYSIS" << endl;

	float maxLength = 0;
	float minLength = 0;
	float averageLength = 0;
	float medianLength = 0;

	vector<float> sortedLines;

	for(int i = 0; i<l.size(); i++)
	{
		sortedLines.push_back(l[i].length);
	}

	for(auto i: sortedLines)
	{
		std:sort(sortedLines.begin(), sortedLines.end());
	}

	for(int i = 0; i<sortedLines.size(); i++)
	{
		//cout << sortedLines[i] << endl;
		averageLength += sortedLines.at(i);
	}

	maxLength = sortedLines.at(sortedLines.size()-1);
	minLength = sortedLines.at(0);
	
	averageLength = averageLength/l.size();

	if(sortedLines.size() > 1)
	{
		if(sortedLines.size()%2 == 0)
		{
			int valOne = int(sortedLines.size()/2);
			int valTwo = valOne-1;

			medianLength = (sortedLines.at(valOne)+sortedLines.at(valTwo))/2;
		}

		else
		{
			medianLength = sortedLines.at(int((sortedLines.size()/2)-1));
		}
	}

	else
	{
		medianLength = sortedLines.at(0);
	}

	//cout << "Max Length: " << maxLength << endl;
	weightVals.push_back(maxLength);
	//cout << "Min Length: " << minLength << endl;
	weightVals.push_back(minLength);
	//cout << "Average Length: " << averageLength << endl;
	weightVals.push_back(averageLength);
	//cout << "Median Length: " << medianLength << endl;
	weightVals.push_back(medianLength);

	cout << "LENGTH ANALYSIS COMPLETE" << endl;
}

void testApp::blackWhite()
{
	cout << "RUNNING BLACK VS. WHITE ANALYSIS" << endl;

	int blackCounter = 0;
	int whiteCounter = 0;

	float BWratio = 0;

	vector<specialPointClass> setPoints;

	for(int i = 0; i<= ofGetWidth(); i+= ofGetWidth()/3)
	{
		for(int j = 0; j<= ofGetHeight(); j+= ofGetHeight()/3)
		{
			setPoints.push_back(specialPointClass(i, j));
		}
	}

	fbo.readToPixels(pix);
	glReadPixels(0, 0, ofGetWidth(), ofGetHeight(), GL_RGB, GL_UNSIGNED_BYTE, pix.getPixels());

	int runCounter = 0;

	for(int i = 0; i< ofGetWidth(); i++)
	{
		//cout << "I : " << i << endl;

		for(int j = 0; j< ofGetHeight(); j++)
		{
			bool black = true;

			ofColor color;
			color = pix[runCounter];
			
			runCounter ++;

			if(color.r == 255)
			{
				whiteCounter++;
				//cout << "WHITE" << endl;
			}
			
			else
			{
				blackCounter++;

				//cout << "BLACK" << endl;

				for(int k = 0; k<setPoints.size(); k++)
				{
					setPoints[k].totalDistance = setPoints[k].totalDistance + getDistance(ofPoint(i, j), ofPoint(setPoints[k].xLoc, setPoints[k].yLoc));
				}
			}
		}
	}

	cout << "Black Counter = " << blackCounter << endl;
	
	if(blackCounter > 0)
	{
		BWratio = whiteCounter/blackCounter;
	}

	else
	{
		BWratio = whiteCounter/1;
	}

	for(int i = 0; i<setPoints.size(); i++)
	{
		setPoints[i].averageDistance = setPoints[i].totalDistance/blackCounter;
		cout << "AverageDistance to Point " << i << " : " << setPoints[i].averageDistance << endl;
		compositionVals.push_back(setPoints[i].averageDistance);
	}

	cout << "Black White Ratio: " << BWratio << endl;
	weightVals.push_back(BWratio);
	weightVals.push_back(blackCounter);
	weightVals.push_back(whiteCounter);

	cout << "BLACK WHITE ANALYSIS COMPLETE" << endl << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//Genetic Funtions
void testApp::iniateGeneticSystem()
{
	cout << "Iniation beginning " << "..." << endl << endl;

	cout << "Please Enter the population size greater than 1" << endl;
	cin >> populationSize;

	while(populationSize <= 1)
	{
		cout << "Please enter a population size greater than 1" << endl;
		cin >> populationSize;
	}

	for(int i = 0; i<populationSize; i++)
	{
		lookie theLookie = lookie();
		theLookie.id = i;
		theLookie.locationFind();
		population.push_back(theLookie);
	}
	for(int i = 0; i<population.size(); i++)
	{
		badPop.push_back(population[i]);
	}
	cout << "Population size: " << population.size() << endl;
	cout << "iniation complete" << endl;
}

void testApp::updateGeneticSystem()
{
	cout << "Updating genetic system" << endl;
	currentHighFit = 0;
	currentLowFit = 7300;

	for(int i = 0; i<badPop.size(); i++)
	{
		badPop[i].fitnessVal = 7300 - badPop[i].fitnessVal;

		if(badPop[i].fitnessVal <= currentLowFit)
		{
			worstLookie = lookie(1);
			worstLookie.numPoints = badPop[i].numPoints;
			worstLookie.numSegments = population[i].numSegments;

			for(int k = 0; k<badPop[i].numPointsPerSeg.size(); k++)
			{
				worstLookie.numPointsPerSeg.push_back(badPop[i].numPointsPerSeg[k]);
			}

			for(int k = 0; k<badPop[i].thePoints.size(); k++)
			{
				worstLookie.thePoints.push_back(badPop[i].thePoints[k]);
			}
		}

		if(badPop[i].fitnessVal <= lowestFitness)
		{
			worstLookie = lookie(1);
			lowestFitness = badPop[i].fitnessVal;
			worstLookie.numPoints = badPop[i].numPoints;
			worstLookie.numSegments = badPop[i].numSegments;
			
			for(int k = 0; k<badPop[i].numPointsPerSeg.size(); k++)
			{
				worstLookie.numPointsPerSeg.push_back(badPop[i].numPointsPerSeg[k]);
			}

			for(int k = 0; k<badPop[i].thePoints.size(); k++)
			{
				worstLookie.thePoints.push_back(badPop[i].thePoints[k]);
			}
		}
	}

	for(int i = 0; i < badPop.size(); i++)
	{
		if(badPop[i].fitnessVal > 0)
		{
			//cout << "Fitness Val = " << population[i].fitnessVal << endl;
			cout << "what n will equal: " << int(ofMap((badPop[i].fitnessVal/currentLowFit), 0, 1, 1, 100)) << endl << endl;
			int n = int(ofMap((badPop[i].fitnessVal/currentLowFit), 0, 1, 1, 100));

			for(int j = 0; j < n; j++)
			{
				putridPool.push_back(badPop[i].id);
			}
		}
	}

	//cout << "Running matingPool loop" << endl;

	for(int i = 0; i < populationSize; i++)
	{
		bool alike = true;
		
		int parentAID = putridPool.at(int(ofRandom(0, putridPool.size())));
		int parentBID = putridPool.at(int(ofRandom(0, putridPool.size())));

		if(parentAID == parentBID)
		{
			//cout << "inside the parentA == parentB statemenet" << endl;

			while(alike)
			{
				//cout << "they are alike" << endl;
				if(parentAID != parentBID)
				{
					alike = false;
				}

				else
				{
					parentAID = putridPool.at(int(ofRandom(0, putridPool.size())));
					parentBID = putridPool.at(int(ofRandom(0, putridPool.size())));
				}
			}
		}
		
		//cout << "About to push back a child" << endl;

		nastyChildren.push_back(crossOver(badPop[parentAID], badPop[parentBID]));
		nastyChildren[i].id = i;
	}

	//cout<< "Children size: " << children.size() << endl;

	badPop.clear();
	putridPool.clear();

	for(int i = 0; i < nastyChildren.size(); i++)
	{
		badPop.push_back(nastyChildren.at(i));
	}

	nastyChildren.clear();

	for(int i = 0; i<population.size(); i++)
	{
		cout << "Population " << i << " Fitness Value: " << population[i].fitnessVal << endl;
		population[i].fitnessVal = 7300 - population[i].fitnessVal;
		//population[i].fitnessVal = ofMap(population[i].fitnessVal, 0, 7300, 100, 0, true);

		if(population[i].fitnessVal >= currentHighFit)
		{
			currentHighFit = population[i].fitnessVal;

			bestLookie = lookie(1);
			//highestFitness = population[i].fitnessVal;
			bestLookie.numPoints = population[i].numPoints;
			bestLookie.numSegments = population[i].numSegments;
			
			for(int k = 0; k<population[i].numPointsPerSeg.size(); k++)
			{
				bestLookie.numPointsPerSeg.push_back(population[i].numPointsPerSeg[k]);
			}

			for(int k = 0; k<population[i].thePoints.size(); k++)
			{
				bestLookie.thePoints.push_back(population[i].thePoints[k]);
			}
			
			cout << "Highest Fitness = " << population[i].fitnessVal << endl;
		}

		if(population[i].fitnessVal >= highestFitness)
		{
			bestLookie = lookie(1);
			highestFitness = population[i].fitnessVal;
			bestLookie.numPoints = population[i].numPoints;
			bestLookie.numSegments = population[i].numSegments;
			
			for(int k = 0; k<population[i].numPointsPerSeg.size(); k++)
			{
				bestLookie.numPointsPerSeg.push_back(population[i].numPointsPerSeg[k]);
			}

			for(int k = 0; k<population[i].thePoints.size(); k++)
			{
				bestLookie.thePoints.push_back(population[i].thePoints[k]);
			}
			
			cout << "Highest Fitness = " << population[i].fitnessVal << endl;
		}
	}

	for(int i = 0; i < population.size(); i++)
	{
		if(population[i].fitnessVal > 0)
		{
			//cout << "Fitness Val = " << population[i].fitnessVal << endl;
			cout << "what n will equal: " << int(ofMap((population[i].fitnessVal/currentHighFit), 0, 1, 1, 100)) << endl << endl;
			int n = int(ofMap((population[i].fitnessVal/currentHighFit), 0, 1, 1, 100));

			for(int j = 0; j < n; j++)
			{
				matingPool.push_back(population[i].id);
			}
		}
	}

	//cout << "Running matingPool loop" << endl;

	for(int i = 0; i < populationSize; i++)
	{
		bool alike = true;
		
		int parentAID = matingPool.at(int(ofRandom(0, matingPool.size())));
		int parentBID = matingPool.at(int(ofRandom(0, matingPool.size())));

		if(parentAID == parentBID)
		{
			//cout << "inside the parentA == parentB statemenet" << endl;

			while(alike)
			{
				//cout << "they are alike" << endl;
				if(parentAID != parentBID)
				{
					alike = false;
				}

				else
				{
					parentAID = matingPool.at(int(ofRandom(0, matingPool.size())));
					parentBID = matingPool.at(int(ofRandom(0, matingPool.size())));
				}
			}
		}
		
		//cout << "About to push back a child" << endl;

		children.push_back(crossOver(population[parentAID], population[parentBID]));
		children[i].id = i;
	}

	//cout<< "Children size: " << children.size() << endl;

	population.clear();
	matingPool.clear();

	for(int i = 0; i < children.size(); i++)
	{
		population.push_back(children.at(i));
	}

	children.clear();
}

void testApp::weaknessTest(int idNum)
{
	weightVals.push_back(badPop[idNum].numPoints); //0
		//cout << "Number of Segments: " << generated.numSegments << endl;
	weightVals.push_back(badPop[idNum].numSegments); //1

	slopeAnalysis(badPop[idNum]);
	angleAnalysis(badPop[idNum]);
	blackWhite();

	//this whole section could definitley be cleaned up. right now i'm multiplying by 0.01 in the find error which
	//changes the number and then i'm mapping it here to change it again. this could be 1 less operation per value
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[0], neuralWeightSystem.wnumPoints),0, 0.5, 0, 1000, true);
	//cout << "numPoints error: " << ofMap(findError(weightVals[0], neuralWeightSystem.wnumPoints), 0, 0.5, 0, 100, true) << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[1], neuralWeightSystem.wnumSegments),0, 0.5, 0, 1000, true);
	//cout << "numSegments error: " << ofMap(findError(weightVals[1], neuralWeightSystem.wnumSegments),0, 0.5, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[2], neuralWeightSystem.wnumSLGroups), 0, 0.05, 0, 100, true);
	//cout << "numSLGroups error: " << ofMap(findError(weightVals[2], neuralWeightSystem.wnumSLGroups), 0, 0.05, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[3], neuralWeightSystem.wSLmax), 0, 0.05, 0, 100, true);
	//cout << "SLMax error: " << ofMap(findError(weightVals[3], neuralWeightSystem.wSLmax), 0, 0.05, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[4], neuralWeightSystem.wnumGroupsWLines), 0, 0.1, 0, 100, true);
	//cout << "numgroupsWLines error: " << ofMap(findError(weightVals[4], neuralWeightSystem.wnumGroupsWLines), 0, 0.1, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[5], neuralWeightSystem.wnumNegativeSL), 0, 0.3, 0, 100, true);
	//cout << "numNegativeSL error: " << ofMap(findError(weightVals[5], neuralWeightSystem.wnumNegativeSL), 0, 0.3, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[6], neuralWeightSystem.wnumPositiveSL), 0, 0.3, 0, 100, true);
	//cout << "numPositiveSL error: " << ofMap(findError(weightVals[6], neuralWeightSystem.wnumPositiveSL), 0, 0.3, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[7], neuralWeightSystem.wratioVH), 0, 0.01, 0, 100, true);
	//cout << ofMap(findError(weightVals[7], neuralWeightSystem.wratioVH), 0, 0.02, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[8], neuralWeightSystem.wratioVD), 0, 0.01, 0, 100, true);
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[9], neuralWeightSystem.wratioHD), 0, 0.01, 0, 100, true);
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[10], neuralWeightSystem.wmaxLength), 0, 5, 0, 100, true);
	//cout << ofMap(findError(weightVals[10], neuralWeightSystem.wmaxLength), 0, 5, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[11], neuralWeightSystem.wminLength), 0, 5, 0, 100, true);
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[12], neuralWeightSystem.waverageLength), 0, 5, 0, 100, true);
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[13], neuralWeightSystem.wmedianLength), 0, 5, 0, 100, true);
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[14], neuralWeightSystem.wnumAngleGroups), 0, 0.05, 0, 100, true);
	//cout << ofMap(findError(weightVals[14], neuralWeightSystem.wnumAngleGroups), 0, 0.05, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[15], neuralWeightSystem.wnumObtuseAngles), 0, 2.5, 0, 100, true);
	//cout << ofMap(findError(weightVals[15], neuralWeightSystem.wnumObtuseAngles), 0, 2.5, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[16], neuralWeightSystem.wnumAcuteAngles), 0, 1, 0, 100, true);
	//cout << ofMap(findError(weightVals[16], neuralWeightSystem.wnumAcuteAngles), 0, 1, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[17], neuralWeightSystem.wnumAngleGroupsWAngles), 0, 0.03, 0, 100, true);
	//cout << ofMap(findError(weightVals[17], neuralWeightSystem.wnumAngleGroupsWAngles), 0, 0.03, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[18], neuralWeightSystem.wnumLowAngles), 0, 0.2, 0, 100, true);
	//cout << ofMap(findError(weightVals[18], neuralWeightSystem.wnumLowAngles), 0, 0.02, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[19], neuralWeightSystem.waverageLowAngleLineLength), 0, 5, 0, 100, true);
	//cout << ofMap(findError(weightVals[19], neuralWeightSystem.waverageLowAngleLineLength), 0, 5, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[20], neuralWeightSystem.wBWratio), 0, 1, 0, 100, true);
	//cout << ofMap(findError(weightVals[20], neuralWeightSystem.wBWratio), 0, 1, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[21], neuralWeightSystem.wblackCounter), 0, 300, 0, 100, true);
	//cout << ofMap(findError(weightVals[21], neuralWeightSystem.wblackCounter), 0, 300, 0, 100, true) << endl << endl;
	badPop[idNum].fitnessVal += ofMap(findError(weightVals[22], neuralWeightSystem.wwhiteCounter), 0, 1500, 0, 100, true);
	//cout << ofMap(findError(weightVals[22], neuralWeightSystem.wwhiteCounter), 0, 1500, 0, 100, true) << endl << endl;

	for(int i = 0; i<neuralWeightSystem.wcompositionPointDistances.size(); i++)
	{
		badPop[idNum].fitnessVal += ofMap(findError(compositionVals[i], neuralWeightSystem.wcompositionPointDistances[i]), 0, 3, 0, 200, true);
		//cout << ofMap(findError(compositionVals[i], neuralWeightSystem.wcompositionPointDistances[i]), 0, 3, 0, 100, true) << endl << endl;
	}

	weightVals.clear();
	compositionVals.clear();
}

void testApp::fitnessTest(int idNum)
{
	weightVals.push_back(population[idNum].numPoints); //0
		//cout << "Number of Segments: " << generated.numSegments << endl;
	weightVals.push_back(population[idNum].numSegments); //1

	slopeAnalysis(population[idNum]);
	angleAnalysis(population[idNum]);
	blackWhite();

	//this whole section could definitley be cleaned up. right now i'm multiplying by 0.01 in the find error which
	//changes the number and then i'm mapping it here to change it again. this could be 1 less operation per value
	population[idNum].fitnessVal += ofMap(findError(weightVals[0], neuralWeightSystem.wnumPoints),0, 0.5, 0, 1000, true);
	//cout << "numPoints error: " << ofMap(findError(weightVals[0], neuralWeightSystem.wnumPoints), 0, 0.5, 0, 100, true) << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[1], neuralWeightSystem.wnumSegments),0, 0.5, 0, 1000, true);
	//cout << "numSegments error: " << ofMap(findError(weightVals[1], neuralWeightSystem.wnumSegments),0, 0.5, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[2], neuralWeightSystem.wnumSLGroups), 0, 0.05, 0, 100, true);
	//cout << "numSLGroups error: " << ofMap(findError(weightVals[2], neuralWeightSystem.wnumSLGroups), 0, 0.05, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[3], neuralWeightSystem.wSLmax), 0, 0.05, 0, 100, true);
	//cout << "SLMax error: " << ofMap(findError(weightVals[3], neuralWeightSystem.wSLmax), 0, 0.05, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[4], neuralWeightSystem.wnumGroupsWLines), 0, 0.1, 0, 100, true);
	//cout << "numgroupsWLines error: " << ofMap(findError(weightVals[4], neuralWeightSystem.wnumGroupsWLines), 0, 0.1, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[5], neuralWeightSystem.wnumNegativeSL), 0, 0.3, 0, 100, true);
	//cout << "numNegativeSL error: " << ofMap(findError(weightVals[5], neuralWeightSystem.wnumNegativeSL), 0, 0.3, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[6], neuralWeightSystem.wnumPositiveSL), 0, 0.3, 0, 100, true);
	//cout << "numPositiveSL error: " << ofMap(findError(weightVals[6], neuralWeightSystem.wnumPositiveSL), 0, 0.3, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[7], neuralWeightSystem.wratioVH), 0, 0.01, 0, 100, true);
	//cout << ofMap(findError(weightVals[7], neuralWeightSystem.wratioVH), 0, 0.02, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[8], neuralWeightSystem.wratioVD), 0, 0.01, 0, 100, true);
	population[idNum].fitnessVal += ofMap(findError(weightVals[9], neuralWeightSystem.wratioHD), 0, 0.01, 0, 100, true);
	population[idNum].fitnessVal += ofMap(findError(weightVals[10], neuralWeightSystem.wmaxLength), 0, 5, 0, 100, true);
	//cout << ofMap(findError(weightVals[10], neuralWeightSystem.wmaxLength), 0, 5, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[11], neuralWeightSystem.wminLength), 0, 5, 0, 100, true);
	population[idNum].fitnessVal += ofMap(findError(weightVals[12], neuralWeightSystem.waverageLength), 0, 5, 0, 100, true);
	population[idNum].fitnessVal += ofMap(findError(weightVals[13], neuralWeightSystem.wmedianLength), 0, 5, 0, 100, true);
	population[idNum].fitnessVal += ofMap(findError(weightVals[14], neuralWeightSystem.wnumAngleGroups), 0, 0.05, 0, 100, true);
	//cout << ofMap(findError(weightVals[14], neuralWeightSystem.wnumAngleGroups), 0, 0.05, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[15], neuralWeightSystem.wnumObtuseAngles), 0, 2.5, 0, 100, true);
	//cout << ofMap(findError(weightVals[15], neuralWeightSystem.wnumObtuseAngles), 0, 2.5, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[16], neuralWeightSystem.wnumAcuteAngles), 0, 1, 0, 100, true);
	//cout << ofMap(findError(weightVals[16], neuralWeightSystem.wnumAcuteAngles), 0, 1, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[17], neuralWeightSystem.wnumAngleGroupsWAngles), 0, 0.03, 0, 100, true);
	//cout << ofMap(findError(weightVals[17], neuralWeightSystem.wnumAngleGroupsWAngles), 0, 0.03, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[18], neuralWeightSystem.wnumLowAngles), 0, 0.2, 0, 100, true);
	//cout << ofMap(findError(weightVals[18], neuralWeightSystem.wnumLowAngles), 0, 0.02, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[19], neuralWeightSystem.waverageLowAngleLineLength), 0, 5, 0, 100, true);
	//cout << ofMap(findError(weightVals[19], neuralWeightSystem.waverageLowAngleLineLength), 0, 5, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[20], neuralWeightSystem.wBWratio), 0, 1, 0, 100, true);
	//cout << ofMap(findError(weightVals[20], neuralWeightSystem.wBWratio), 0, 1, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[21], neuralWeightSystem.wblackCounter), 0, 300, 0, 100, true);
	//cout << ofMap(findError(weightVals[21], neuralWeightSystem.wblackCounter), 0, 300, 0, 100, true) << endl << endl;
	population[idNum].fitnessVal += ofMap(findError(weightVals[22], neuralWeightSystem.wwhiteCounter), 0, 1500, 0, 100, true);
	//cout << ofMap(findError(weightVals[22], neuralWeightSystem.wwhiteCounter), 0, 1500, 0, 100, true) << endl << endl;

	for(int i = 0; i<neuralWeightSystem.wcompositionPointDistances.size(); i++)
	{
		population[idNum].fitnessVal += ofMap(findError(compositionVals[i], neuralWeightSystem.wcompositionPointDistances[i]), 0, 3, 0, 200, true);
		//cout << ofMap(findError(compositionVals[i], neuralWeightSystem.wcompositionPointDistances[i]), 0, 3, 0, 100, true) << endl << endl;
	}

	weightVals.clear();
	compositionVals.clear();
}

float testApp::findError(float aVal, float bVal)
{ 
	float error = abs(aVal - bVal);
	error *= 0.01;

	return error;
}

lookie testApp::crossOver(lookie parentA, lookie parentB)
{
	//my first attempt at this function was forgetful of the possibility
	//of mutation in offspring so i need a mutation function to allow for
	//new segments to be inserted

	//cout << "Running Crossover" << endl;

	vector<vector<ofPoint>> segmentsA;
	vector<vector<ofPoint>> segmentsB;
	
	float mutationRate = 5;
	int pointIndexA = 0;
	int pointIndexB = 0;

	for(int i = 0; i<parentA.numPointsPerSeg.size(); i++)
	{
		vector<ofPoint> newVector;
		segmentsA.push_back(newVector);

		for(int j = 0; j<parentA.numPointsPerSeg[i]; j++)
		{
			segmentsA[i].push_back(parentA.thePoints[pointIndexA]);
			pointIndexA++;
		}
	}

	for(int i = 0; i<parentB.numPointsPerSeg.size(); i++)
	{
		vector<ofPoint> newVector;
		segmentsB.push_back(newVector);

		for(int j = 0; j<parentB.numPointsPerSeg[i]; j++)
		{
			segmentsB[i].push_back(parentB.thePoints[pointIndexB]);
			pointIndexB++;
		}
	}

	//cout << "SegmentA Size: " << segmentsA.size() << endl;
	//cout << "SegmentB Size: " << segmentsB.size() << endl;

	//the segment vectors are now filled with vectors of points the create 
	//each segment. so i can create a child by pulling segments from the 
	//vectors

	lookie childLookie = lookie(1);

	int selector = int(ofRandom(0, 100));

	//first i have to decide how many segments will be in the child
	//so I choose one of the values from the parents

	if(selector > 49)
	{
		childLookie.numSegments = parentA.numSegments;
		//cout << "Childlookie numSegments: " << childLookie.numSegments << endl;
	}
	else
	{
		childLookie.numSegments = parentB.numSegments;
		//cout << "Childlookie numSegments: " << childLookie.numSegments << endl;
	}

	//now that i know how many segments the child will have I want to
	//add segments to the child randomly
	int randomTop = 100;

	for(int i = 0; i<childLookie.numSegments; i++)
	{
		//this value decides from which parent the segment will be taken
		int newSelector = int(ofRandom(0, randomTop - mutationRate));

		if(newSelector >= int((randomTop-mutationRate)/2) && newSelector < randomTop)
		{
			//here i am checking to make sure the parent selected has enough segments
			//to grab one from the "i" value place. if it doesn't then i take the
			//segment from the other parent
			if(segmentsA.size()-1 >= i)
			{
				for(int j = 0; j<segmentsA[i].size(); j++)
				{
					childLookie.thePoints.push_back(segmentsA[i].at(j));
					childLookie.numPoints++;
				}

				childLookie.numPointsPerSeg.push_back(segmentsA[i].size());
			}

			else
			{
				for(int j = 0; j<segmentsB[i].size(); j++)
				{
					childLookie.thePoints.push_back(segmentsB[i].at(j));
					childLookie.numPoints++;
				}

				childLookie.numPointsPerSeg.push_back(segmentsB[i].size());
			}
		}

		else if(newSelector < int((randomTop - mutationRate)/2))
		{
			if(segmentsB.size()-1 >= i)
			{
				for(int j = 0; j<segmentsB[i].size(); j++)
				{
					childLookie.thePoints.push_back(segmentsB[i].at(j));
					childLookie.numPoints++;
				}

				childLookie.numPointsPerSeg.push_back(segmentsB[i].size());
			}	

			else
			{
				for(int j = 0; j<segmentsA[i].size(); j++)
				{
					childLookie.thePoints.push_back(segmentsA[i].at(j));
					childLookie.numPoints++;
				}

				childLookie.numPointsPerSeg.push_back(segmentsA[i].size());
			}
		}

		else if(newSelector >= randomTop - mutationRate)
		{
			int numPointsInSegment = int(ofRandom(segmentsA[i].size(), segmentsB[i].size()));
			childLookie.numPointsPerSeg.push_back(numPointsInSegment);

			for(int k = 0; k< numPointsInSegment; k++)
			{
				ofPoint myNewPoint = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
				childLookie.thePoints.push_back(myNewPoint);
				childLookie.numPoints++;
			}
		}

	}

	return childLookie;
}