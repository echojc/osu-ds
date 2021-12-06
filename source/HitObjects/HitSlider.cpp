#include "HitSlider.h"

HitSlider::HitSlider(s32 x, s32 y, s32 time, u32 lengthtime, vector<HitObjectPoint*>& points, vector<HitObjectPoint*>& ticks, u32 repeats, HitObjectType type, HitObjectSound sound)
	: HitObject(x, y, time, type, sound)
{
	fTouching = false;
	fStarted = false;
	fFinished = false;
	mTimeLast = time;
	mChannel = -1;
	
	u32 pointCount = points.size();
	u32 tickCount = ticks.size();
	
	mTickCount = tickCount;
	mTicksHit = 0;
	mRepeats = repeats;
	mRepeatCurrent = 0;
	mTicksTarget = (tickCount + 1) * repeats + 1;
	
	mTicks = new TickSprites[tickCount];
	mTickTimes = new s32[mTicksTarget-1];
	
	u32 beatTime = BeatmapElements::Element().GetTimingPoint(time).BeatTime;
	
	//populate tick times excluding first hit
	mTickTime = beatTime / DifficultyManager::SliderTickRate;
	u32 specialTickTime = lengthtime - mTickCount*mTickTime;
	
	//easy if we don't have any ticks, just keep adding lengthtime
	if (tickCount == 0)
	{
		for (u32 i=0; i<mTicksTarget-1; ++i)
		{
			mTickTimes[i] = time + (lengthtime * (i+1));
		}
	}
	else
	{
		//the reason for the lengthiness is because the time between the final
		//tick and the slider end is not necessarily the same as mTickTime
		//then there is the reversal of ticks when going backwards
		
		//long story short - it just works :D
		
		u32 iterator = 0;
		while (iterator < repeats)
		{
			u32 j;
			for (u32 i=0; i<tickCount; ++i)
			{
				j = iterator*(tickCount+1)+i;
				if (j==0)
					mTickTimes[0] = time + mTickTime;
				else
					mTickTimes[j] = mTickTimes[j-1] + mTickTime;
			}
			mTickTimes[iterator*(tickCount+1)+tickCount] = mTickTimes[j] + specialTickTime;
			
			++iterator;
			
			if (iterator < repeats)
			{
				mTickTimes[iterator*(tickCount+1)] = mTickTimes[iterator*(tickCount+1)-1] + specialTickTime;
				for (u32 i=1; i<tickCount+1; ++i)
				{
					j = iterator*(tickCount+1)+i;
					mTickTimes[j] = mTickTimes[j-1] + mTickTime;
				}
			}
			++iterator;
		}
	}
	
	u32 circleSize = DifficultyManager::GetCircleSize();
	u32 ballSize = (circleSize >> 3) * 7; // 7/8 size
	u32 tickSize = circleSize >> 2; // 1/4 size
	
	u32 preempt = DifficultyManager::GetPreemptTime();
	s32 fadeInStart = time - preempt;
	s32 fadeInEnd = fadeInStart + (preempt >> 3);
	mEndTime = time + (repeats * lengthtime);
	mLengthTime = lengthtime;
	
	pSprite* spr;
	
	//todo: fix formula
	//u32 fps = (u32)(DifficultyManager::SliderMultiplier*3.142*ballSize*1000/beatTime);
	u32 fps = 60;
	
	//slider ball
	spr = new pAnimation(TX_PLAY_SLIDERB0, 10, fps, x, y, ballSize, ballSize, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
	spr->Show(time);
	MapSliderPath(spr, points, time, lengthtime, repeats);
	spr->Kill(mEndTime);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_SLIDERFOLLOW, x, y, ballSize, ballSize, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
	spr->Scale(time, time+50, 1, 2);
	spr->Scale(mEndTime, mEndTime+50, 2, 1.5);
	MapSliderPath(spr, points, time, lengthtime, repeats);
	spr->Kill(mEndTime+100);
	mSprites.push_back(spr);
	
	if ((repeats&0x1)==1) //if ODD score is at end
	{
		mScoreSpriteId = 6;
		mSecondaryScoreSpriteId = 4;
	}
	else
	{
		mScoreSpriteId = 4;
		mSecondaryScoreSpriteId = 6;
	}
	
	//slider start
	spr = new pSprite(TX_PLAY_CIRCLEAPPROACH, x, y, circleSize, circleSize, ORIGIN_CENTER, FIELD_PLAY, mColour, 0);
	spr->Show(fadeInStart, fadeInEnd);
	spr->Hide(time, time+100);
	spr->Scale(fadeInStart, time, 4, 1);
	spr->Kill(mEndTime);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_CIRCLEOVERLAY, x, y, circleSize, circleSize, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
	spr->Show(fadeInStart, fadeInEnd);
	spr->Kill(mEndTime+1000);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_CIRCLE, x, y, circleSize, circleSize, ORIGIN_CENTER, FIELD_PLAY, mColour, 0);
	spr->Show(fadeInStart, fadeInEnd);
	spr->Kill(mEndTime+1000);
	mSprites.push_back(spr);
	
	//slider end
	spr = new pSprite(TX_PLAY_CIRCLEOVERLAY, points[pointCount-1]->x, points[pointCount-1]->y, circleSize, circleSize, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
	spr->Show(fadeInStart, fadeInEnd);
	spr->Kill(mEndTime+1000);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_CIRCLE, points[pointCount-1]->x, points[pointCount-1]->y, circleSize, circleSize, ORIGIN_CENTER, FIELD_PLAY, mColour, 0);
	spr->Show(fadeInStart, fadeInEnd);
	spr->Kill(mEndTime+1000);
	mSprites.push_back(spr);
	
	//slider30 sprites
	spr = new pSprite(TX_PLAY_SLIDER30, points[0]->x, points[0]->y, 40, 40, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
	spr->Kill(mEndTime+1000);
	mSprites.push_back(spr);
	
	spr = new pSprite(TX_PLAY_SLIDER30, points[pointCount-1]->x, points[pointCount-1]->y, 40, 40, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
	spr->Kill(mEndTime+1000);
	mSprites.push_back(spr);
	
	//slider repeats
	for (u32 i=1; i<repeats; ++i) //start at 1 because no repeats if repeats==1
	{
		HitObjectPoint* p;
		s32 tAnimStart, tFadeInEnd, tAngle;
		
		if ((i&0x1)==0) //if even - slider start
		{
			p = points[0];
			tAngle = p->angle;
			//animations shifted until number disappears
			tAnimStart = time;
			tFadeInEnd = tAnimStart + (preempt >> 3);
		}
		else //if odd - slider end
		{
			p = points[pointCount-1];
			tAngle = p->angle + 0x4000;
			tAnimStart = fadeInStart;
			tFadeInEnd = fadeInEnd;
		}
		
		spr = new pSprite(TX_PLAY_SLIDERREVERSE, p->x, p->y, ballSize, ballSize, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
		spr->Show(tAnimStart, tFadeInEnd);
		//todo: slider repeat explosion?
		spr->Hide(time+(lengthtime*i));
		
		//animate arrow
		do
		{
			s32 tAnimEnd = tAnimStart + 500;
			spr->Rotate(tAnimStart, tAnimEnd, tAngle, tAngle+3000);
			spr->Scale(tAnimStart, tAnimEnd, 1, 0.9);
			tAnimStart = tAnimEnd;
		} while (tAnimStart < time+(lengthtime*i));
		
		spr->Kill(mEndTime);
		mSprites.push_back(spr);
	}
	
	//slider ticks & score sprites
	for (u32 i=0; i<tickCount; ++i)
	{
		spr = new pSprite(TX_PLAY_SLIDERTICK, ticks[i]->x, ticks[i]->y, tickSize, tickSize, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31), 0);
		spr->Show(fadeInStart, fadeInEnd);
		spr->Hide(mEndTime, mEndTime+120);
		spr->Kill(mEndTime+120);
		mSprites.push_back(spr);
		
		//add to list for tracking ticks
		mTicks[i].Tick = spr;
		
		spr = new pSprite(TX_PLAY_SLIDER10, ticks[i]->x, ticks[i]->y, 40, 40, ORIGIN_CENTER, FIELD_PLAY, RGB15(31,31,31),0);
		spr->Kill(mEndTime+1000);
		mSprites.push_back(spr);
		
		//add to list as well
		mTicks[i].Score = spr;
	}
	
	//slider path
	for (u32 i=0; i<pointCount; ++i)
	{
		spr = new pSprite(TX_PLAY_DISC, points[i]->x, points[i]->y, ballSize, ballSize, ORIGIN_CENTER, FIELD_PLAY, mColour, 0, 0.015f);
		spr->Show(fadeInStart+30, fadeInEnd);
		spr->Hide(mEndTime-30, mEndTime+70);
		spr->Kill(mEndTime+70);
		mSprites.push_back(spr);
	}
}

HitSlider::~HitSlider()
{
	delete mTicks;
	delete mTickTimes;
	
	if (mChannel != -1)
		AudioManager::Engine().StopChannel(mChannel);
}

bool HitSlider::InBounds(s32 x, s32 y)
{
	//hit is based on sliderfollowcircle
	return mSprites[1]->InBounds(x, y);
}

void HitSlider::Update()
{
	s32 now = GameClock::Clock().Time();
	
	//trigger score calculation once slider is finished
	if (now >= mEndTime)
		Hit();
	
	//process slider behaviour
	{
		//find the next tick
		u32 i = 0;
		for (; i < mTicksTarget; ++i)
		{
			if (mTickTimes[i] > mTimeLast)
				break;
		}
		
		//mTickTimes[i] now refers to the time for the next tick
		
		//any normal tick/slider repeat
		if (i < mTicksTarget-2) //why? try it on a piece of paper >.>
		{
			//if we passed over a tick or repeat
			if (mTickTimes[i] <= now)
			{
				//if it's a tick we hide it and bounce the followcircle
				if ((i+1)%(mTickCount+1) != 0)
				{
					if (fTouching)
					{
						u32 real;
						
						//fairly straightfoward if this is the first (or only) repeat
						if (mRepeatCurrent == 0)
						{
							real = i;
						}
						//when we have repeats, we have to calculate the "real" tick
						else
						{
							real = i - (mRepeatCurrent * (mTickCount+1));
							//however if repeat is ODD we have to count BACKWARDS >.>
							if ((mRepeatCurrent & 0x1) == 1)
							{
								real = (mTickCount-1) - real;
							}
						}
						
						++mTicksHit;
						mTicks[real].Tick->Hide();
						mSprites[1]->Scale(now, now+60, 2.5, 2);
						
						//slider10 animation
						mTicks[real].Score->Show();
						mTicks[real].Score->Hide(now+300, now+350);
						mTicks[real].Score->Move(now, now+250,
												mTicks[real].Tick->X, mTicks[real].Tick->Y,
												mTicks[real].Tick->X, mTicks[real].Tick->Y - 20);
						mTicks[real].Score->Move(now+250, now+320, 
												mTicks[real].Tick->X, mTicks[real].Tick->Y - 20,
												mTicks[real].Tick->X, mTicks[real].Tick->Y - 30);
						
						//normal ticks give 10 points
						IncreaseScore(SCORE_TICK_10, false, true);
						AudioManager::Engine().PlaySliderTick();
					}
					else //if we missed a tick
					{
						IncreaseScore(SCORE_MISS, true, true);
					}
				}
				//otherwise it's a repeat and we'll need to reset the ticks
				else
				{
					if (fTouching)
					{
						++mTicksHit;
						mSprites[1]->Scale(now, now+60, 2.5, 2);
						
						u32 tSpriteId;
						
						if ((mRepeatCurrent&1)==1) //if ODD
							tSpriteId = 7;
						else
							tSpriteId = 8;
						
						mSprites[tSpriteId]->Show();
						mSprites[tSpriteId]->Hide(now+300, now+350);
						mSprites[tSpriteId]->Move(now, now+250, mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y - 20);
						mSprites[tSpriteId]->Move(now+250, now+320, mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y - 20,
											mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y - 30);
						mSprites[tSpriteId]->Move(now+350, now+350, mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y);
						
						//repeats give 30 points
						IncreaseScore(SCORE_TICK_30, false, true);
						AudioManager::Engine().PlayHitSound(mSound);
					}
					else
					{
						IncreaseScore(SCORE_MISS, true, true);
					}
				}
			}
		}
		//slider end
		else if (fTouching && !fFinished && i == mTicksTarget-2) //again, try it on a piece of paper if you want to know why >.>
		{
			if (now >= mEndTime - DifficultyManager::GetHitWindow300()) //hack - seems like we're missing a frame somewhere >.>
			{
				++mTicksHit;
				
				u32 tSpriteId;
				
				if ((mRepeats&1)==0) //if EVEN - mRepeats is always greater than the maximum value of mRepeatCurrent by 1
					tSpriteId = 7;
				else
					tSpriteId = 8;
				
				mSprites[tSpriteId]->Show();
				mSprites[tSpriteId]->Hide(now+300, now+350);
				mSprites[tSpriteId]->Move(now, now+250, mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y - 20);
				mSprites[tSpriteId]->Move(now+250, now+320, mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y - 20,
									mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y - 30);
				mSprites[tSpriteId]->Move(now+350, now+350, mSprites[tSpriteId]->X, mSprites[tSpriteId]->Y);
				
				IncreaseScore(SCORE_TICK_30, true, true);
				fFinished = true;
			}
		}
	}
	
	//reset ticks if ball goes to a repeat regardless of fTouching
	if (now >= mTime + (mLengthTime * (mRepeatCurrent + 1)))
	{
		for (u32 j=0; j<mTickCount; ++j)
		{
			//no need to reshow visible sprites
			if (mTicks[j].Tick->Alpha != 31)
				mTicks[j].Tick->Show(now, now+50);
		}
		++mRepeatCurrent;
	}
	
	mTimeLast = now;
}

void HitSlider::OnTouchDown(const touchPosition& touch)
{
	if (InBounds(touch.px, touch.py))
	{
		s32 now = GameClock::Clock().Time();
		u32 delta = MathHelper::Abs(mTime - now);
		
		//slider start
		if (delta < DifficultyManager::GetHitWindow() && !fStarted)
		{
			//fTouching = true; //set in OnTouch() which will always be called if OnTouchDown() is called
			fStarted = true;
			mSprites[1]->Transform(TR_FADE, now, mEndTime, 31, 31);
			mSprites[2]->Kill(now);
			
			//if it was hit within the window for any amount of points
			if (delta < DifficultyManager::GetHitWindow50())
			{
				++mTicksHit;
				
				mSprites[7]->Show();
				mSprites[7]->Hide(now+300, now+350);
				mSprites[7]->Move(now, now+250, mSprites[7]->X, mSprites[7]->Y - 20);
				mSprites[7]->Move(now+250, now+320, mSprites[7]->X, mSprites[7]->Y - 20,
									mSprites[7]->X, mSprites[7]->Y - 30);
				mSprites[7]->Move(now+350, now+350, mSprites[7]->X, mSprites[7]->Y);
				
				IncreaseScore(SCORE_TICK_30, false, true);
				AudioManager::Engine().PlayHitSound(mSound);
			}
			else
			{
				IncreaseScore(SCORE_MISS, true, true);
			}
		}
		
		if (mChannel == -1)
			mChannel = AudioManager::Engine().PlaySliderSound(mSound);
	}
}

void HitSlider::OnTouch(const touchPosition& touch)
{
	s32 now = GameClock::Clock().Time();
	u32 delta = MathHelper::Abs(mTime - now);
	
	if (InBounds(touch.px, touch.py) && now >= mTime && now <= mEndTime + DifficultyManager::GetHitWindow())
	{
		//if we're touching it without tapping it, then we missed the slider start
		if (delta < DifficultyManager::GetHitWindow() && !fStarted)
		{
			fStarted = true;
			IncreaseScore(SCORE_MISS, true, true);
		}
		
		mSprites[1]->Transform(TR_FADE, now, mEndTime, 31, 31);
		fTouching = true;
		//mTimeLast = now; //set in Update()
		
		if (mChannel == -1)
			mChannel = AudioManager::Engine().PlaySliderSound(mSound);
	}
	else
	{
		//touching screen but not sprite is the same as not touching at all
		OnTouchUp(touch);
	}
}

void HitSlider::OnTouchUp(const touchPosition& touch)
{
	s32 now = GameClock::Clock().Time();
	mSprites[1]->Transform(TR_FADE, now, mEndTime, 0, 0);
	
	if (mChannel != -1)
	{
		AudioManager::Engine().StopChannel(mChannel);
		mChannel = -1;
	}
	
	fTouching = false;
}

void HitSlider::Hit()
{
	if (mTicksHit == 0)
	{
		IncreaseScore(SCORE_MISS);
		IncreaseScore(SCORE_MISS, true, false, mSecondaryScoreSpriteId); //miss shows on both slider start and end
		
		//fade hitcircles
		for (u32 i=3; i<=6; ++i)
		{
			mSprites[i]->Transform(TR_FADE, mEndTime, mEndTime+100, 31, 0);
		}
	}
	else
	{
		if (mTicksHit == mTicksTarget)
		{
			IncreaseScore(SCORE_300);
		}
		else if (mTicksHit >= mTicksTarget>>1) //at least half were hit
		{
			IncreaseScore(SCORE_100);
		}
		else if (mTicksHit > 0)
		{
			IncreaseScore(SCORE_50);
		}
		
		//animate hitcircles
		for (u32 i=3; i<=6; ++i)
		{
			mSprites[i]->Transform(TR_FADE, mEndTime, mEndTime+200, 31, 10);
			mSprites[i]->Transform(TR_FADE, mEndTime+200, mEndTime+270, 10, 0);
			mSprites[i]->Scale(mEndTime, mEndTime+150, 1, 1.7);
			mSprites[i]->Scale(mEndTime+150, mEndTime+270, 1.7, 1.9);
		}
		
		AudioManager::Engine().PlayHitSound(mSound);
		
		if (mChannel != -1)
		{
			AudioManager::Engine().StopChannel(mChannel);
			mChannel = -1;
		}
	}
	
	mHit = true;
}

void HitSlider::MapSliderPath(pSprite* spr, vector<HitObjectPoint*>& points, s32 time, u32 lengthtime, u32 repeats)
{
	u32 timeperpoint = lengthtime / points.size();
	
	u32 loops = 0;
	while (loops < repeats)
	{
		for (u32 i=0; i<points.size()-1; ++i)
		{
			spr->Move(time+(loops*lengthtime)+(timeperpoint*i), time+(loops*lengthtime)+(timeperpoint*(i+1)), points[i]->x, points[i]->y, points[i+1]->x, points[i+1]->y);
			spr->Rotate(time+(loops*lengthtime)+(timeperpoint*i), time+(loops*lengthtime)+(timeperpoint*(i+1)), points[i]->angle, points[i+1]->angle);
		}
		++loops;
		
		if (loops < repeats)
		{
			for (u32 i=0; i<points.size()-1; ++i)
			{
				spr->Move(time+(loops*lengthtime)+(timeperpoint*i), time+(loops*lengthtime)+(timeperpoint*(i+1)), points[points.size()-i-1]->x, points[points.size()-i-1]->y, points[points.size()-i-2]->x, points[points.size()-i-2]->y);
				spr->Rotate(time+(loops*lengthtime)+(timeperpoint*i), time+(loops*lengthtime)+(timeperpoint*(i+1)), points[points.size()-i-1]->angle+0x4000, points[points.size()-i-2]->angle+0x4000);
			}
			++loops;
		}
	}
}

