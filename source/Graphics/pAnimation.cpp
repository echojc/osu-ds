#include "pAnimation.h"

pAnimation::pAnimation(TextureType texture, u32 framecount, u32 fps, s32 x, s32 y, u32 width, u32 height, DrawOrigin origin, FieldType type, rgb color, u32 alpha)
	: pSprite(texture, x, y, width, height, origin, type, color, alpha)
{
	mFrameCount = framecount;
	mFrameCurrent = 0;
	mOrigTexture = texture;
	
	mUpdatesPerFrame = 60.0 / fps;
	mUpdatesWaited = 0;
}

void pAnimation::Update()
{
	while (mUpdatesWaited >= mUpdatesPerFrame)
	{
		mUpdatesWaited -= mUpdatesPerFrame;
		
		++mFrameCurrent;
		if (mFrameCurrent >= mFrameCount)
			mFrameCurrent = 0;
		
		Texture = (TextureType)(mOrigTexture + mFrameCurrent);
	}
	
	++mUpdatesWaited;
	
	pSprite::Update();
}