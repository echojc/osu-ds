#include "GameBase.h"

GameBase::GameBase()
{
	BeatmapManager::BuildCollection();
	//ChangeMode(MODE_PLAYER);
	ChangeMode(MODE_SONGSELECT);
}

void GameBase::Update()
{
	Mode::CurrentMode().HandleInput();
	Mode::CurrentMode().Update();
}

