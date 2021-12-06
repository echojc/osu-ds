#include "Transformation.h"

Transformation::Transformation(TransformType type, s32 starttime, s32 endtime, s32 startvalue, s32 endvalue)
{
	this->type = type;
	
	this->starttime = starttime;
	this->endtime = endtime;
	
	this->startvalue = startvalue;
	this->endvalue = endvalue;
	
	totaltime = endtime-starttime;
	totalvalue = endvalue-startvalue;
	
	currentvalue = startvalue;
	
	active = false;
	lastactive = false;
}

void Transformation::Update()
{
	s32 time = GameClock::Clock().Time();
	
	if (!active)
	{
		if (time > starttime)
			active = true;
		else
			return;
	}
	
	if (time > endtime)
	{
		active = false;
		currentvalue = endvalue;
		lastactive = true;
		return;
	}
	
	currentvalue = (s32)(((time-starttime)/(float)totaltime)*totalvalue + startvalue);
}

bool Transformation::Active()
{
	if (lastactive)
	{
		lastactive = false;
		return true;
	}
	return active;
}
