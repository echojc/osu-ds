#include "InputHelper.h"

touchPosition InputHelper::mTouch;

bool InputHelper::KeyDown(int key)
{
	return keysDown() & key;
}

bool InputHelper::KeyHeld(int key)
{
	return keysHeld() & key;
}

bool InputHelper::KeyUp(int key)
{
	return keysUp() & key;
}

touchPosition& InputHelper::TouchRead()
{
	touchRead(&mTouch);
	
	mTouch.px *= 2.5;
	mTouch.py *= 2.5;
	
	return mTouch;
}

