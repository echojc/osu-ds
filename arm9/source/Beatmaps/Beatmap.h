#include <nds.h>
#include <string.h>
#include <unistd.h>
#include <list>
#include <vector>
#include <string>

#include "BeatmapElements.h"

#include "System/GameClock.h"
#include "Helpers/FileReader.h"
#include "Helpers/MathHelper.h"

#include "HitObjects/HitObject.h"
#include "HitObjects/HitCircle.h"
#include "HitObjects/HitSlider.h"
#include "HitObjects/HitSpinner.h"

#include "Graphics/SpriteManager.h"

#ifndef __BEATMAP_H__
#define __BEATMAP_H__

using namespace std;

//typedef list<HitObject*>::iterator hitObjectIterator;

class Beatmap
{
	public:
		Beatmap(const char* filename, const char* basedir);
		virtual ~Beatmap();
		
		void Initialize();
		void CleanUp();
		
		void Buffer(list<HitObject*>& hitObjectList);
		bool GameOver() { return mHitObjectRead == mHitObjectCount && GameClock::Clock().Time() >= mLastObjectEndTime + 3000; }
		
		string& Filename() { return mFilename; }
		string& Title() { return mTitle; }
		string& Artist() { return mArtist; }
		string& Creator() { return mCreator; }
		string& Version() { return mVersion; }
		string& AudioFilename() { return mAudioFilename; }
		
		string& BaseDir() { return mBaseDir; }
		
		s32 SkipTime() { return mSkipTime; }
		s32 StartTime() { return mFirstObjectTime; }
	
	protected:
		FileReader* mReader;
		
		u32 mHitObjectCount, mHitObjectRead;
		s32 mFirstObjectTime, mLastObjectEndTime;
		
		void ReadNextObject();
		s32 mNextObjectTime;
		s32 mNextObjectX, mNextObjectY;
		HitObjectType mNextObjectType;
		
		s32 mSkipTime;
		bool mForceNewCombo;
		
		bool fReady, fLoadable;
		
		string mFilename;
		string mTitle;
		string mArtist;
		string mCreator;
		string mVersion;
		string mAudioFilename;
		
		string mBaseDir;
};

#endif

