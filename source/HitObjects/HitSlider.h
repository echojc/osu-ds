#include <nds.h>
#include <vector>
#include "HitObject.h"

#ifndef __HITSLIDER_H__
#define __HITSLIDER_H__

using namespace std;

typedef vector<HitObjectPoint*>::iterator pointIterator;

typedef struct {
	pSprite* Tick;
	pSprite* Score;
} TickSprites;

class HitSlider : public HitObject
{
	public:
		HitSlider(s32 x, s32 y, s32 time, u32 lengthtime, vector<HitObjectPoint*>& points, vector<HitObjectPoint*>& ticks, u32 repeats, HitObjectType type, HitObjectSound sound);
		~HitSlider();
		
		bool InBounds(s32 x, s32 y);
		
		void Update();
		
		void OnTouchDown(const touchPosition& touch);
		void OnTouch(const touchPosition& touch);
		void OnTouchUp(const touchPosition& touch);
		
		void Hit();
	
	protected:
		static void MapSliderPath(pSprite* spr, vector<HitObjectPoint*>& points, s32 time, u32 lengthtime, u32 repeats);
		
		bool fTouching, fStarted, fFinished;
		TickSprites* mTicks;
		s32* mTickTimes;
		u32 mTickTime, mLengthTime;
		
		u32 mTickCount, mTicksHit, mTicksTarget;
		u32 mRepeats, mRepeatCurrent;
		s32 mTimeLast;
		
		u32 mSecondaryScoreSpriteId;
		
		int mChannel;
};

#endif

