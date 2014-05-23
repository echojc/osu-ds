#include <nds.h>
#include <stdio.h>
#include "System/GameClock.h"

#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

typedef enum {
	TR_FADE,
	TR_MOVEX,
	TR_MOVEY,
	TR_SCALEX,
	TR_SCALEY,
	TR_ROTATE,
	TR_KILL
} TransformType;

class Transformation
{
	public:
		Transformation(TransformType type, s32 starttime, s32 endtime, s32 startvalue, s32 endvalue);
		void Update();
		s32 Value() const { return currentvalue; }
		bool Active();
		TransformType Type() const { return type; }
		
		bool Finished() { return GameClock::Clock().Time() > endtime; }
	
	protected:
		TransformType type;
		
		bool active, lastactive;
		
		s32 starttime, endtime, totaltime;
		
		s32 startvalue, endvalue, currentvalue;
		s32 totalvalue;
};


#endif

