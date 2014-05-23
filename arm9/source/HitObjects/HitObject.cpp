#include "HitObject.h"

rgb HitObject::mColour = 0;
float HitObject::sScoreDeltaZ = 0;
float HitObject::sSliderDeltaZ = 0;
s32 HitObject::sLastSliderTime = 0;
ICallback* HitObject::mScoreCallback = NULL;

HitObject::HitObject(s32 x, s32 y, s32 time, HitObjectType type, HitObjectSound sound)
{
	mX = x;
	mY = y;
	mTime = time;
	mType = type;
	mHit = false;
	mSound = sound;
	
	mScoreSpriteId = 0;
	
	mComboEnd = false;
	
	if ((type & HIT_COMBO) > 0)
		mColour = BeatmapElements::Element().GetNextColour();
}

HitObject::~HitObject()
{
}

void HitObject::Hit()
{
	mHit = true;
}

void HitObject::IncreaseScore(ScoreType score, bool forceNoCombo, bool forceNoAnimation)
{
	IncreaseScore(score, forceNoCombo, forceNoAnimation, mScoreSpriteId);
}

void HitObject::IncreaseScore(ScoreType score, bool forceNoCombo, bool forceNoAnimation, u32 spriteId)
{
	HitObjectPoint point = {
		mSprites[spriteId]->X,
		mSprites[spriteId]->Y,
		0
	};
	
	void** args = new void*[5];
	
	ARGS_PUSH(args, 0, score);
	ARGS_PUSH(args, 1, forceNoCombo);
	ARGS_PUSH(args, 2, forceNoAnimation);
	ARGS_PUSH(args, 3, point);
	ARGS_PUSH(args, 4, mComboEnd);
	
	if (mScoreCallback != NULL)
		mScoreCallback->DoCallback(args);
	
	delete[] args;
}

void HitObject::SetScoreCallback(ICallback* scoreCallback)
{
	//if (mScoreCallback != NULL)
	//	delete mScoreCallback;
	
	mScoreCallback = scoreCallback;
}

void HitObject::SetPostCreateOptions(bool comboend, s32 nextx, s32 nexty)
{
	//set whether this is the last object of a combo
	mComboEnd = comboend;
	/*
	//set score z layering
	mScoreDeltaZ = sScoreDeltaZ;
	
	if (sScoreDeltaZ >= 0.05f || MathHelper::Abs(mSprites[mScoreSpriteId]->x() - nextx) + MathHelper::Abs(mSprites[mScoreSpriteId]->y() - nexty) >= 230)
		sScoreDeltaZ = 0;
	else
		sScoreDeltaZ += 0.001f;
	
	//set slider z layering	
	if (sSliderDeltaZ >= 0.05f || mTime - DifficultyManager::GetPreemptTime() > sLastSliderTime)
		sSliderDeltaZ = 0;
	else
		sSliderDeltaZ += 0.004f;
	
	if ((mType & HIT_SLIDER) > 0)
	{
		for (spriteIterator it = mSprites.begin(); it != mSprites.end(); ++it)
		{
			if (*it != NULL)
			{
				(*it)->SetDeltaZ(sSliderDeltaZ);
			}
		}
		
		sLastSliderTime = mEndTime;
	}
	*/
}

