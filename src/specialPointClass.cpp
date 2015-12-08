#include "specialPointClass.h"

specialPointClass::specialPointClass()
{
}

specialPointClass::specialPointClass(int xLocation, int yLocation)
{
	xLoc = xLocation;
	yLoc = yLocation;
	totalDistance = 0;
	averageDistance = 0;
}

specialPointClass::~specialPointClass()
{
}

void specialPointClass::drawDot()
{
	ofFill();
	ofSetColor(255, 0, 0);
	ofEllipse(xLoc, yLoc, 10, 10);
}

