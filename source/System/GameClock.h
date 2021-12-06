#include <nds.h>

#ifndef __GAMECLOCK_H__
#define __GAMECLOCK_H__

class GameClock
{
	public:
		s32 Time();
		
		void Update(); //calls should be synced with vblank
		void SkipTo(s32 time);
		void Reset();
		
		static GameClock& Clock() { return sClock; }
	
	protected:
		s32 mTime;
		s32 mFraction;
		
		static const s32 kTimeInterval = 16;
		static const s32 kFractionInterval = 715112635;
		
		static GameClock sClock;
	
	private:
		GameClock();
		~GameClock() {}
};

#endif

