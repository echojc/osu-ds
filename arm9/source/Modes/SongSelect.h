#include <nds.h>
#include <stdio.h>

#include "Mode.h"
#include "Beatmaps/BeatmapManager.h"
#include "Graphics/SpriteManager.h"
#include "System/TextManager.h"

#ifndef __SONGSELECT_H__
#define __SONGSELECT_H__

class SongSelect : public Mode
{
	public:
		SongSelect();
		~SongSelect();
		
		void Update();
		void HandleInput();
	
	protected:
		SpriteManager mSpriteManager;
		
		static const s32 kSongListXOffset = 37;
		static const s32 kSongListYOffset = 80;
		static const s32 kSongListSpacing = 203;
		
		s32 mCurrentX;
		s32 mDeltaX;
		s32 mIndex;
		
		u32 mColTarget;
		u32 mColCurrent;
		u32 mColMax;
		u32 mColSpill;
		
		void MoveSongList(s32 x);
		void MoveSongListLeft();
		void MoveSongListRight();
};

#endif

