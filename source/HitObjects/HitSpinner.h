#include <nds.h>
#include <math.h>
#include "HitObject.h"

#ifndef __HITSPINNER_H__
#define __HITSPINNER_H__

class HitSpinner : public HitObject
{
	public:
		HitSpinner(s32 time, s32 endtime, HitObjectSound sound);
		~HitSpinner();
		
		void Update();
		
		void OnTouchDown(const touchPosition& touch);
		void OnTouch(const touchPosition& touch);
		
		void Hit();
	
	protected:
		s32 GetAngle(s32 x, s32 y);
		
		s32 mLastAngle;
		bool fSpinning;
		s32 mDirection, mZeroPoint;
		float mTotalRotation;
		u32 mCurrentRotation;
		u32 mTotalSpins;
		u32 mRequiredSpins;
		
		u32* mUV;
		
		int mChannel;
};

#endif


