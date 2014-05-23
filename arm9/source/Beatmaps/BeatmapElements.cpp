#include "BeatmapElements.h"

BeatmapElements BeatmapElements::sInstance;

const TimingPoint& BeatmapElements::GetTimingPoint(s32 time)
{
/*
	u32 i;
	for (i=0; i<mTimingPoints.size(); ++i)
	{
		if (mTimingPoints[i].Time > time)
			break;
	}
	return mTimingPoints[MathHelper::Max(i-1, 0)];
*/
	u32 i;
	for (
		i = mTimingPoints.size() - 1;
		i > 0 && mTimingPoints[i].Time > time;
		--i
	);
	return mTimingPoints[i];
}

const TimingPoint& BeatmapElements::GetTimingPoint()
{
	return GetTimingPoint(GameClock::Clock().Time());
}

const bool BeatmapElements::IsBreak()
{
	for (u32 i=0; i<mBreakPoints.size(); ++i)
	{
		if (GameClock::Clock().Time() > mBreakPoints[i].StartTime && GameClock::Clock().Time() < mBreakPoints[i].EndTime)
			return true;
	}
	return false;
}

rgb BeatmapElements::GetNextColour()
{
	//backwards compatibility - increase counter BEFORE returning
	if (++mCurrentColour >= mColours.size())
		mCurrentColour = 0;
	
	return mColours[mCurrentColour];
}

void BeatmapElements::AddTimingPoint(s32 time, float beattime, u8 samplesetid)
{
	TimingPoint tPoint = {
		time,
		beattime,
		samplesetid
	};
	
	mTimingPoints.push_back(tPoint);
}

void BeatmapElements::AddBreakPoint(s32 start, s32 end)
{
	BreakPoint bPoint = {
		start,
		end
	};
	
	mBreakPoints.push_back(bPoint);
}

void BeatmapElements::ResetColours(bool fill)
{
	mColours.clear();
	mCurrentColour = 0;
	
	if (fill)
	{
		mColours.push_back(RGB15(31,18,0));
		mColours.push_back(RGB15(1,30,1));
		mColours.push_back(RGB15(1,1,30));
		mColours.push_back(RGB15(30,1,1));
	}
}
