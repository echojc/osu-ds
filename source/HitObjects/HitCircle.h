#include <nds.h>
#include "HitObject.h"

#ifndef __HITCIRCLE_H__
#define __HITCIRCLE_H__

class HitCircle : public HitObject
{
	public:
		HitCircle(s32 x, s32 y, s32 time, HitObjectType type, HitObjectSound sound);
		
		bool InBounds(s32 x, s32 y);
		
		void OnTouchDown(const touchPosition& touch);
		
		void Hit();
};

#endif


