#include <nds.h>
#include <stdio.h>
#include <string>
#include <dirent.h>
#include <string.h>
#include <vector>

#include "Beatmap.h"
#include "BeatmapElements.h"
#include "DifficultyManager.h"
#include "Modes/Mode.h"

#ifndef __BEATMAPMANAGER_H__
#define __BEATMAPMANAGER_H__

using namespace std;

typedef vector<Beatmap*>::iterator beatmapIterator;

class BeatmapManager
{
	public:
		static Beatmap& Current() { return *mBeatmapCurrent; }
		
		static void BuildCollection();
		static void Load(u32 index);
		static u32 MapCount();
		static u32 SongCount();
		
		static vector<Beatmap*>& Beatmaps() { return mBeatmaps; }
	
	protected:
		static Beatmap* mBeatmapCurrent;
		
		static vector<Beatmap*> mBeatmaps;
};

#endif

