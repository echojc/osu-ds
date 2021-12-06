#include "HitSpinner.h"

HitSpinner::HitSpinner(s32 time, s32 endtime, HitObjectSound sound) : HitObject(256, 192, time, HIT_SPINNER, sound)
{
	mEndTime = endtime;
	fSpinning = false;
	
	mDirection = 0; //0 = not set, values -1 and 1 used
	mZeroPoint = 0; //point to start counting rotations from
	mTotalRotation = 0; //counts rotations in current direction (resets)
	mCurrentRotation = 0; //keeps track of which rotation we are at to count
	mTotalSpins = 0; //counts total number of spins
	mRequiredSpins = (mEndTime - mTime) / DifficultyManager::GetSpinnerTime(); //total spins required
	
	mUV = new u32[4]; //deleted by pSprite
	mUV[0] = TEXTURE_PACK(inttot16(0),inttot16(0));
	mUV[1] = TEXTURE_PACK(inttot16(256),inttot16(0));
	mUV[2] = TEXTURE_PACK(inttot16(256),inttot16(192));
	mUV[3] = TEXTURE_PACK(inttot16(0),inttot16(192));
	
	pSprite* spr;
	
	spr = new pSprite(TX_PLAY_CIRCLEAPPROACH, 256, 192, 440, 440, ORIGIN_CENTER, FIELD_PLAY, RGB15(10,10,31), 0);
	spr->Show(time-300, time);
	spr->Hide(endtime, endtime+300);
	spr->Scale(time-300, endtime, 1, 0);
	spr->Kill(endtime+300);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_SPINNER, 256, 192, 400, 400, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0, 0.03f);
	spr->Show(time-300, time);
	spr->Hide(endtime, endtime+300);
	spr->Kill(endtime+300);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_SPINNERBARS, 0, 480, 640, 480, ORIGIN_BOTTOMLEFT, FIELD_SCREEN, RGB15(31,31,31), 0, 0.03f);
	spr->Show(time-300, time);
	spr->Hide(endtime, endtime+300);
	spr->Kill(endtime+300);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_SPINNERBG, 320, 240, 640, 480, ORIGIN_CENTER, FIELD_SCREEN, RGB15(31,31,31), 0, 0.05f);
	spr->Show(time-300, time+300);
	spr->Hide(endtime, endtime+300);
	spr->Kill(endtime+300);
	mSprites.push_back(spr);
	
	mScoreSpriteId = 1;
	
	mSprites[2]->UV = mUV;
	mChannel = -1;
}

HitSpinner::~HitSpinner()
{
	if (mChannel != -1)
			AudioManager::Engine().StopChannel(mChannel);
}

void HitSpinner::Update()
{
	float ratio = (mTotalSpins + MathHelper::Frc(mTotalRotation)) / mRequiredSpins;
	
	//set spinner bars
	u32 height = MathHelper::Max(0, MathHelper::Min(192, ratio*192) - MathHelper::Random(0,10));
	
	mUV[0] = TEXTURE_PACK(inttot16(0),inttot16(192-height));
	mUV[1] = TEXTURE_PACK(inttot16(256),inttot16(192-height));
	mSprites[2]->Height = height*2.5;
	
	//set spinner sound
	if (mChannel == -1 && GameClock::Clock().Time() >= mTime)
		mChannel = AudioManager::Engine().PlaySample(SOUND_DATA(spinnerspin_bin), true);
	
	if (mChannel != -1)
		AudioManager::Engine().SetChannelFreq(mChannel, MathHelper::Min((u32)(10000 + (ratio * 30000)), 65535));
	
	//trigger score calculation once slider is finished
	if (GameClock::Clock().Time() >= mEndTime)
		Hit();
}

void HitSpinner::OnTouchDown(const touchPosition& touch)
{
	if (GameClock::Clock().Time() >= mTime && GameClock::Clock().Time() <= mEndTime)
	{
		mLastAngle = GetAngle(touch.px, touch.py);
		fSpinning = true;
	}
}

void HitSpinner::OnTouch(const touchPosition& touch)
{
	if (GameClock::Clock().Time() >= mTime && GameClock::Clock().Time() <= mEndTime)
	{
		if (MathHelper::Abs(touch.px - 320) < 10 && MathHelper::Abs(touch.py - 265) < 10)
		{
			fSpinning = false;
			return;
		}
		
		//work out the new angle
		s32 newAngle = GetAngle(touch.px, touch.py);
		
		if (!fSpinning)
		{
			mLastAngle = newAngle;
			fSpinning = true;
			return;
		}
		
		if (newAngle == mLastAngle)
			return;
		
		s32 deltaAngle = newAngle - mLastAngle;
		
		//hack for passing through line x=320 where y<265
		if (deltaAngle > 16384)
			deltaAngle -= 32768;
		else if (deltaAngle < -16384)
			deltaAngle += 32768;
		
		mSprites[1]->Angle += deltaAngle;
		
		//if player changes direction add to total rotations and start count again
		if (mDirection != MathHelper::Sgn(deltaAngle))
		{
			mDirection = MathHelper::Sgn(deltaAngle);
			mZeroPoint = mSprites[1]->Angle;
			mTotalRotation = 0;
			mCurrentRotation = 0;
		}
		
		mTotalRotation = MathHelper::Abs(mSprites[1]->Angle - mZeroPoint) / 32768.0;
		
		//if we have made an extra circle (or more) add to total
		if (mCurrentRotation < (u32)mTotalRotation)
		{
			mTotalSpins += (u32)mTotalRotation - mCurrentRotation;
			mCurrentRotation = (u32)mTotalRotation;
			
			IncreaseScore(SCORE_SPIN_100, true, true);
			if (mTotalSpins > mRequiredSpins)
			{
				IncreaseScore(SCORE_SPIN_1000, true, true);
				AudioManager::Engine().PlaySample(SOUND_DATA(spinnerbonus_bin));
			}
		}
		
		mLastAngle = newAngle;
	}
}

void HitSpinner::Hit()
{
	if (mRequiredSpins > 0 && (mTotalSpins == 0 || mTotalSpins < MathHelper::Max(0, (s32)(mRequiredSpins - 2))))
	{
		IncreaseScore(SCORE_MISS);
	}
	else
	{
		//compatibility with osu!pc
		if (mRequiredSpins == 0)
		{
			IncreaseScore(SCORE_50, false, true); //score sprite doesn't show if you score 50 on spinners
		}
		else if (mTotalSpins >= mRequiredSpins)
		{
			IncreaseScore(SCORE_300);
		}
		else if (mTotalSpins == MathHelper::Max(0, (s32)(mRequiredSpins - 1)))
		{
			IncreaseScore(SCORE_100);
		}
		else if (mTotalSpins == MathHelper::Max(0, (s32)(mRequiredSpins - 2)))
		{
			IncreaseScore(SCORE_50, false, true); //score sprite doesn't show if you score 50 on spinners
		}
		
		AudioManager::Engine().PlayHitSound(mSound);
	}
	
	if (mChannel != -1)
		AudioManager::Engine().StopChannel(mChannel);
	
	mHit = true;
}

s32 HitSpinner::GetAngle(s32 x, s32 y)
{
	float theta = atan((float)(y-265)/(x-320));
	s32 angle = theta*32768/6.2832;
	
	//hack - let's hope this won't come back to haunt me
	if (x < 320)
		angle += 16384;
	
	return angle;
}