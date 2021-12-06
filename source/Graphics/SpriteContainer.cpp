#include "SpriteContainer.h"

SpriteContainer::~SpriteContainer()
{
	if (mSpriteOwner)
	{
		for (spriteIterator it = mSprites.begin(); it != mSprites.end(); ++it)
		{
			if (*it != NULL)
				delete *it;
		}
	}
}

void SpriteContainer::AddToSpriteManager(SpriteManager& spriteManager)
{
	spriteManager.Add(mSprites);
	
	//once sprites are added to spritemanager, the memory
	//belongs to the spritemanager, and should be deleted by it
	mSpriteOwner = false;
}

