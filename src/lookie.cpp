#include "lookie.h"

lookie::lookie()
{
	//cout << "Running lookie" << endl;
	fitnessVal = 0;
	numPoints = int(ofRandom(10, 50));
	numSegments = int(ofRandom(1,numPoints/2));
	
	//cout << "Number of Points and Segments Generated" << endl;
	//cout << "Points: " << numPoints << endl;
	//cout << "Segments: " << numSegments << endl;

	int pointsLeft = numPoints;

	for(int i = 0; i<numSegments; i++)
	{
		if(pointsLeft > 1)
		{
			//cout << "NUMBER POINTS LEFT: " << pointsLeft << endl;

			int pointsInSeg = int(ofRandom(2, pointsLeft));

			numPointsPerSeg.push_back(pointsInSeg);

			pointsLeft -= pointsInSeg;
		}

		// i ran into an issue with the vector subscipt being out of range because 
		//in my slope analysis function i was using the number of segments variable to
		//do a for loop but without this else statement the number of segments and the 
		//number of indices of the numPointsPerSeg variable would not be similar
		else
		{
			numPointsPerSeg.push_back(0);
		}
	}
}

lookie::lookie(int uh)
{
	fitnessVal = 0;
	numPoints = 0;
	numSegments = 0;
}

lookie::~lookie()
{
}

void lookie::locationFind()
{
	//cout << "RUNNING LOCATION FIND" << endl;

	for(int i = 0; i<numPoints; i++)
	{
		thePoints.push_back(ofPoint(ofVec2f(ofRandom(-150, ofGetWidth()+150),ofRandom(-150, ofGetHeight()+150))));
	}

	//cout << "LOCATION FIND COMPLETE" << endl;
}

void lookie::draw()
{
	//cout << "RUNNING DRAW" << endl;

	int pointIndexCount = 0;

	for(int i = 0; i<numPointsPerSeg.size(); i++)
	{
		ofFill();
		//cout << "SEGMENT LOOP" << endl;

		vector<ofPoint> pointArray;

		for(int j = 0; j<numPointsPerSeg[i]; j++)
		{
			//cout << "Number of Points in this segment: " << numPointsPerSeg[i] << endl;

			pointArray.push_back(thePoints[pointIndexCount]);
			pointIndexCount++;

			//cout << "Complete Segment" << endl;
		}

		//cout << "NOW DRAWING SEGMENT" << endl;

		//ofMesh yourLine(OF_PRIMITIVE_LINE_LOOP, pointArray);
		ofMesh yourLine(OF_PRIMITIVE_TRIANGLE_FAN, pointArray);
		ofSetColor(0);
		yourLine.drawWireframe();

		//cout << "SEGMENT DRAWN" << endl;
	}
}