#include <nds.h>

#ifndef __INPUTHELPER_H__
#define __INPUTHELPER_H__

class InputHelper
{
	public:
		static bool KeyDown(int key);
		static bool KeyHeld(int key);
		static bool KeyUp(int key);
		static touchPosition& TouchRead();
	
	protected:
		static touchPosition mTouch;
};

#endif

