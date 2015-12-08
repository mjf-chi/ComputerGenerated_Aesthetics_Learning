#include "slopeLineGroup.h"

slopeLineGroup::slopeLineGroup()
{
}

slopeLineGroup::slopeLineGroup(float min, float max, int n)
{
	minSlope = min*n;
	maxSlope = max*n;
}

slopeLineGroup::~slopeLineGroup()
{
}