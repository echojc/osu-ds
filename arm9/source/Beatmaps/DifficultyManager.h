#include <nds.h>

#ifndef __DIFFICULTYMANAGER_H__
#define __DIFFICULTYMANAGER_H__

class DifficultyManager
{
	public:
		static u8 DifficultyHpDrain;
		static u8 DifficultyCircleSize;
		static u8 DifficultyOverall;
		static float SliderMultiplier;
		static float SliderTickRate;
		static float DifficultyHpDrainRate;
		static u8 DifficultyPeppyStars;
		static float DifficultyEyupStars;
		
		//inline
		static u32 GetCircleSize()		{ return circleSize[DifficultyCircleSize]; } //possibly *1.2
		static u32 GetPreemptTime()		{ return preemptTime[DifficultyOverall]; }
		static u32 GetHitWindow300()	{ return hitWindow300[DifficultyOverall]; }
		static u32 GetHitWindow100()	{ return hitWindow100[DifficultyOverall]; }
		static u32 GetHitWindow50()		{ return hitWindow50[DifficultyOverall]; }
		static u32 GetHitWindow()		{ return hitWindow50[DifficultyOverall] << 1; }
		static u32 GetSpinnerTime()		{ return spinnerTime[DifficultyOverall]; }
		static s32 GetMissHpDrain()		{ return missHpDrain[DifficultyHpDrain]; }
	
	protected:
		static u32 preemptTime[];
		static u32 circleSize[];
		static u32 hitWindow300[];
		static u32 hitWindow100[];
		static u32 hitWindow50[];
		static u32 spinnerTime[];
		static s32 missHpDrain[];
};

#endif

