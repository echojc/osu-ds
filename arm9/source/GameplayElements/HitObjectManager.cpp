#include "HitObjectManager.h"

HitObjectManager::~HitObjectManager()
{
	//delete hitobjects
	for (hitObjectIterator it = mHitObjects.begin(); it != mHitObjects.end(); ++it)
	{
		if (*it != NULL)
			delete *it;
	}
}

void HitObjectManager::Add(HitObject* object)
{
	mHitObjects.push_back(object);
}

void HitObjectManager::HandleInput()
{
	touchPosition touch = InputHelper::TouchRead();
	
	HitObject* hitObject;
	
	// remove all hitobjects before the current time and all hitobjects that have been hit
	bool process = true;
	while (process)
	{
		process = false;
		
		if (mHitObjects.size() == 0)
			return;
		
		// process hitobjects one at a time
		hitObject = mHitObjects.front();
		
		if (hitObject->GetEndTime() <= GameClock::Clock().Time() || hitObject->GetHit() == true)
		{
			// sprites are handled by spritemanager and will not be deleted (see HitObject.h)
			
			// TODO: this is a bit hacky - find a way to guarantee this won't cause a crash
			if (GameClock::Clock().Time() - hitObject->GetEndTime() < 1000 && hitObject->GetHit() == false)
				hitObject->Hit();
			
			mHitObjects.pop_front();
			delete hitObject;
			
			process = true;
		}
	}
	
	// now we are left with the next hitobject that can react to user interaction
	
	if (InputHelper::KeyDown(KEY_TOUCH))
		hitObject->OnTouchDown(touch);
	
	if (InputHelper::KeyHeld(KEY_TOUCH))
		hitObject->OnTouch(touch);
	
	if (InputHelper::KeyUp(KEY_TOUCH))
		hitObject->OnTouchUp(touch);
	
	hitObject->Update();

/*
	//get the first unhit hitobject
	if (mHitObjects.size() == 0)
		return;
	
	HitObject* hitObject = mHitObjects.front();
	
	//only the topmost object can be hit at any time
	if (hitObject->GetEndTime() <= GameClock::Clock().Time() && hitObject->GetHit() == false)
	{
		hitObject->Hit();
	}
	
	if (hitObject->GetHit() == true)
	{
		//sprites are handled by spritemanager and will not be deleted (see HitObject.h)
		delete hitObject;
		mHitObjects.pop_front();
		
		if (mHitObjects.size() == 0)
			return;
		
		hitObject = mHitObjects.front();
	}
	
	//at this point hitObject is pointing to the topmost unhit object if such an object exists
	if (hitObject != NULL)
	{
		if (InputHelper::KeyDown(KEY_TOUCH))
			hitObject->OnTouchDown(touch);
		
		if (InputHelper::KeyHeld(KEY_TOUCH))
			hitObject->OnTouch(touch);
		
		if (InputHelper::KeyUp(KEY_TOUCH))
			hitObject->OnTouchUp(touch);
		
		hitObject->Update();
	}
*/
}