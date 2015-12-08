#include "lookieLines.h"

lookieLines::lookieLines()
{
}

lookieLines::lookieLines(ofPoint f, ofPoint s)
{
	vertical = false;
	negativeS = false;

	//"f" = first point
	//"s" = second point
	a = f;
	b = s;

	//equation for slope of a line 
	//m = (y2-y1)/(x2-x1)
	if((s.x-f.x)!=0)
	{
		slope = float((s.y-f.y)/(s.x-f.x));
		if(slope < 0)
		{
			negativeS = true;
		}
	}

	else
	{
		vertical = true;
		slope = NULL;
	}

	//equation for distance on a cartesian plane
	//d = sqrt(x2 - x1)^2 +(y2 - y1)^2
	length = float(sqrt(((s.x-f.x)*(s.x-f.x)) + ((s.y-f.y)*(s.y-f.y))));
}

lookieLines::~lookieLines()
{
}
