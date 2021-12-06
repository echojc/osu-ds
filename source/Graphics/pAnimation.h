#include <nds.h>
#include "pSprite.h"

#ifndef __PANIMATION_H__
#define __PANIMATION_H__

class pAnimation : public pSprite
{
	public:
		pAnimation(TextureType texture, u32 framecount, u32 fps, s32 x, s32 y, u32 width, u32 height, DrawOrigin origin, FieldType type, rgb color, u32 alpha);
		void Update();
	
	protected:
		TextureType mOrigTexture;
		float mUpdatesPerFrame;
		float mUpdatesWaited;
		u32 mFrameCurrent;
		u32 mFrameCount;
};

#endif

