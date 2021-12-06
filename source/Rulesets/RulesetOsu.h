#include <nds.h>
#include <stdio.h>

#include "Ruleset.h"
#include "HitObjects/HitObject.h"
#include "System/ICallback.h"

#ifndef __RULESETOSU_H__
#define __RULESETOSU_H__

class RulesetOsu : public Ruleset, public ICallback
{
	public:
		RulesetOsu();
		~RulesetOsu() {}
		
		void IncreaseScore(ScoreType score, bool forceNoCombo, bool forceNoAnimation, HitObjectPoint point, bool comboEnd);
		void OnSkip();
		void OnGameOver();
		
		void DoCallback(void** args);
	
	protected:
		u32 mSpecialScore;
		float mScoreZ;
};

#endif

