#include "Ruleset.h"

Ruleset::Ruleset()
{
	mLifebar.AddToSpriteManager(mSpriteManager);
}

void Ruleset::Initialize()
{
	mLifebar.Initialize();
}

void Ruleset::Skip()
{
	if (GameClock::Clock().Time() < BeatmapManager::Current().SkipTime())
	{
		AudioManager::Engine().MusicSkipTo(BeatmapManager::Current().SkipTime());
		GameClock::Clock().SkipTo(BeatmapManager::Current().SkipTime());
		
		// template hook
		OnSkip();
	}
}

void Ruleset::OnGameOver()
{
}

void Ruleset::Update()
{
	list<HitObject*> hitObjectList;
	BeatmapManager::Current().Buffer(hitObjectList);
	
	for (hitObjectIterator it = hitObjectList.begin(); it != hitObjectList.end(); ++it)
	{
		HitObject* object = *it;
		mHitObjectManager.Add(object);
		object->AddToSpriteManager(mSpriteManager);
	}
	
	mLifebar.Update();
	mSpriteManager.Draw();
	
	// score/combo output
	
	TextManager::Bottom().SetFont(FONT_SCORE);
	
	TextManager::Bottom().PrintLocate(635, 5, ORIGIN_TOPRIGHT, "  %08i", mScoreManager.Score());
	
	if (mScoreManager.Combo() > 0)
		TextManager::Bottom().PrintLocate(5, 475, ORIGIN_BOTTOMLEFT, "%ix    ", mScoreManager.Combo());
	else
		TextManager::Bottom().PrintLocate(5, 475, ORIGIN_BOTTOMLEFT, "       ");
}

void Ruleset::HandleInput()
{
	mHitObjectManager.HandleInput();
}

