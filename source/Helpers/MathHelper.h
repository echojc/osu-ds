#include <nds.h>
//#include <math.h>

#ifndef __MATHHELPER_H__
#define __MATHHELPER_H__

class MathHelper
{
	public:
		static u32		Abs(s32 value) { return (value > 0 ? value : -value); }
		static s32		Max(s32 value1, s32 value2) { return (value1 > value2 ? value1 : value2); }
		static s32		Min(s32 value1, s32 value2) { return (value1 < value2 ? value1 : value2); }
		static s32		Sgn(s32 value) { return (value == (s32)Abs(value) ? 1 : -1); }
		static float	Frc(float value) { return value - (int)value; }
		
		static u16 Random(u16 min, u16 max);
	
	protected:
		static u16 mSeed;
};

#endif



