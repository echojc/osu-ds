#include <nds.h>
#include <stdio.h>
#include <vector>

#include "pSprite.h"
#include "SpriteManager.h"

#ifndef __SPRITECONTAINER_H__
#define __SPRITECONTAINER_H__

using namespace std;

typedef vector<pSprite*>::iterator spriteIterator;

/* a generic base class for all objects that require sprites
 * sprite cleanup is automatically handled
 */
class SpriteContainer
{
	public:
		virtual ~SpriteContainer();
		void AddToSpriteManager(SpriteManager& spriteManager);
	
	protected:
		vector<pSprite*> mSprites;
	
	private:
		bool mSpriteOwner;
};

#endif

