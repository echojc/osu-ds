#include <nds.h>
#include <vector>

#include "pSprite.h"
#include "GraphicsManager.h"

#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

using namespace std;

typedef vector<pSprite*>::iterator spriteIterator;
typedef vector<pSprite*>::const_iterator spriteIteratorConst;

class SpriteManager
{
	public:
		SpriteManager();
		virtual ~SpriteManager();
		
		void Draw();
		
		void Add(pSprite* spr);
		void Add(const vector<pSprite*>& spr);
		
		vector<pSprite*>& Sprites() { return mSprites; }
	
	protected:
		vector<pSprite*> mSprites;
};

#endif

