#include "defines.h"

#include "Mode.h"

Mode* Mode::sCurrentMode = NULL;

void Mode::ChangeToOsuDir()
{
#ifdef HARDWARE
	chdir("fat:/osuds");
#else
	chdir("nitro:/osuds");
#endif
}
