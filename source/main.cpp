#include "defines.h"

#include <nds.h>
#include <fat.h>
#include "System/GameBase.h"
#include "System/GameClock.h"
#include "Libraries/nitrofs.h"

#include "System/TextManager.h"

#include "Libraries/gfxconsole.h"

#include "exception.c"

int getFreeRAM();

void vBlankHandler()
{
	GameClock::Clock().Update();
}

int main()
{
	powerOn(POWER_ALL);
	lcdMainOnBottom();
	//defaultExceptionHandler();
	setExceptionHandler(customHandler);
	
	TextManager::Init();
	
	irqEnable(IRQ_VBLANK);
	irqSet(IRQ_VBLANK, vBlankHandler);
	
#ifdef HARDWARE
	if (!fatInitDefault())
	{
		iprintf("fat init error\nplease check dldi patch");
		return -1;
	}
#else
	nitroFSInit("osuds.nds");
#endif
	
	GameBase osu;
	
	swiWaitForVBlank(); //allows key statuses to reset
	while(1)
	{	
		scanKeys();
		
		osu.Update();
		
		glFlush(1);
		
		TextManager::Top().SetFont(FONT_CONSOLE);
		TextManager::Top().Print("\x1b[0;0HTIME: %i     ",GameClock::Clock().Time());
		TextManager::Top().Print("\x1b[1;0HVCOUNT: %i   ", REG_VCOUNT);
		//TextManager::Top().Print("\x1b[2;0HRAM: %i   ", getFreeRAM());
		
		swiWaitForVBlank();
	}

	return 0;
}

int getFreeRAM() 
{ 
    int q = 2*1024*1024;   // 2 Mb 
    int size = q; 
    void *ptr; 
  
    do {    
        ptr = malloc(size); 
  
        if(ptr) { 
            free(ptr); 
        } else { 
            size -= q; 
        } 
        q /= 2; 
        size += q;        
  
    } while(q > 0); 
  
    return size; 
}

