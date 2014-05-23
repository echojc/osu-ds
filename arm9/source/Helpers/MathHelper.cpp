#include "MathHelper.h"

u16 MathHelper::mSeed = 3246;

u16 MathHelper::Random(u16 min, u16 max)
{
	mSeed= 1664525*mSeed+1013904223;
	return (mSeed % (max-min) + min);
}


