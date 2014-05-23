/*---------------------------------------------------------------------------------

	Graphic Console functions

	Copyright (C) 2009
		Steven Harrison

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.

	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you
		must not claim that you wrote the original software. If you use
		this software in a product, an acknowledgment in the product
		documentation would be appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and
		must not be misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source
		distribution.


---------------------------------------------------------------------------------*/

/*! \file gfxconsole.h
    \brief nds graphical stdio support.

<div class="fileHeader">
Provides stdio integration for printing to the DS screen as well as debug print
functionality provided by stderr.

General usage is to initialize the console by:
gfxconsoleDemoInit()
or to customize the console usage by:
gfxconsoleInit()

The default instance utilizes the sub display, using the graphic mode 5_2D, and 
background 3

Debug printing is performed by initializing the debug console via gfxconsoleDebugInit() as 
follows:

<pre>
gfxconsoleDebugInit(DebugDevice_NOCASH);
fprintf(stderr, "debug message in no$gba window %i", stuff);

OR

gfxconsoleDebugInit(DebugDevice_CONSOLE);
fprintf(stderr, "debug message on DS console screen");
</pre>

The print console must be initialized to use DB_CONSOL

</div>

*/

#ifndef GFXCONSOLE_H
#define GFXCONSOLE_H

#include <nds/ndstypes.h>
#include <nds/arm9/background.h>

// include the header file for the default font data - should be in the data folder
//#include "4x6_a_bmf.h" /*!< Default monospaced font >*/
//#include "gc_def_c_bmf.h" /*!< Default multicolored font (actualy 13 colors in this font data) >*/

#include "ByteMapFont.h"

#ifdef __cplusplus
extern "C" {
#endif

extern BMFont gfx_default_font_mono;
//extern BMFont gfx_default_font_mcol;

typedef bool(* gfxConsolePrint)(void* con, char c);


/**
 * \struct gfxPrintConsole
 * \brief console structure used to store the state of a console render context
 
 Default values from gfxconsoleNew():
<div class="fixedFont"><pre>
gfxPrintConsole gfxdefaultConsole = 
{
	//Font:
	(BMFont *) &gfx_default_font_mono,	// Font information
	(u16 *) 0,							// Background buffer
	RGB5( 31, 31, 31 ) | BIT(15),		// Text color - warning here
	RGB5(  0,  0,  0 ) | BIT(15),		// Background color
	-1,									// bg id
	false,								// Bacground mode
	1,									// Use line height for y offsets
	0,0,								// cursorX cursorY
	0,0,								// prevcursorX prevcursorY
	256,								// console width
	192,								// console height
	0,									// window x
	0,									// window y
	256,								// window width
	192,								// window height
	3,									// tab size
	0,									// print callback
	false,								// console initialized
	true,								// load graphics
};
</pre></div>

 */
typedef struct 
{
	BMFont *font[10];			/*!< Pointer to the font data*/
	u8 curFont;					/*!< Current font*/
	u8 numFonts;				/*!< Number of fonts loaded into this console*/

	u16* buffer;				/*!< Pointer to the buffer to write to.  Is set by bgInit*/
	
	u16 textcolor;				/*!< The current text color*/
	u16 backcolor;				/*!< The current background color*/
	
	int bgId;					/*!< bgId, should be set with a call to bgInit() or bgInitSub()*/

	bool backOpaque;			/*!< The background mode - Transparent = false, Opaque = true*/
	
	u8 lineType;				/*!< The line type - 0 = pixel y positions, 1 = line hieght positions*/

	int cursorX;				/*!< Current X location of the cursor (as a tile offset by default)*/
	int cursorY;				/*!< Current Y location of the cursor (as a tile offset by default)*/

	int prevCursorX;			/*!< Internal state*/
	int prevCursorY;			/*!< Internal state*/

	int consoleWidth;			/*!< Width of the console hardware layer in pixels*/
	int consoleHeight;			/*!< Height of the console hardware layer in pixels*/

	int windowX;				/*!< Window X location in pixels (not implemented)*/
	int windowY;				/*!< Window Y location in pixels (not implemented)*/
	int windowWidth;			/*!< Window width in pixels (not implemented)*/
	int windowHeight;			/*!< Window height in pixels (not implemented)*/

	int tabSize;				/*!< Size of a tab*/

	gfxConsolePrint PrintChar;	/*!< callback for printing a character.  Should return true if it has handled rendering the graphics (else the print engine will attempt to render via tiles)*/

	bool consoleInitialised;	/*!< True if the console is initialized*/
	bool loadGraphics;			/*!< True if consoleInit should attempt to load font graphics into background memory*/
	
} gfxPrintConsole;

/*! \fn void gfxConsoleSetFont(gfxPrintConsole* console, BMFont* font)

	\brief Loads the font into the specified console  
	\param console pointer to the print console to update
	\param font the font to load
	*/
void gfxConsoleSetFont(gfxPrintConsole* console, u8 fontNumber);

/*! \fn void gfxConsoleAddFont(gfxPrintConsole* console, BMFont* font)

	\brief Adds the font into the specified console  
	\param console pointer to the print console to update
	\param font the font to add
	\return the position in the font list. or -1 on error
	*/
int gfxConsoleAddFont(gfxPrintConsole* console, BMFont* font);

/*! \fn void gfxConsoleSetWindow(gfxPrintConsole* console, int x, int y, int width, int height)

	\brief Sets the print window
	\param console console to set, if NULL will set current console window
	\param x x location of the window
	\param y y location of the window
	\param width width of the window
	\param height height of the window

	*/
void gfxConsoleSetWindow(gfxPrintConsole* console, int x, int y, int width, int height);

/*! \fn gfxPrintConsole* gfxConsoleGetDefault(void)
	\brief Gets a pointer to the default console (this should only be used when using a single console, other wise use consoleNew(PrintsConsole* console)
	\return A pointer to the default console	
*/
gfxPrintConsole* gfxConsoleGetDefault(void);

/*! \fn void gfxConsoleSelect(gfxPrintConsole* console)
	\brief Make the specified console the render target
	\param console A pointer to the console struct (must have been initialized with consoleInit(PrintConsole* console)
*/
void gfxConsoleSelect(gfxPrintConsole* console);

/*! \fn gfxPrintConsole* gfxConsoleInit(gfxPrintConsole* console, BgType type, BgSize size, bool mainDisplay, bool loadGraphics);

	\brief Initialise the console.
	\param console A pointer to the console initialze data (if null default console will be used)
	\param type the type of the background
	\param size the size of the background
	\param mainDisplay if true main engine is used, otherwise false
	\param loadGraphics if true the default font graphics will be loaded into the layer
*/
gfxPrintConsole* gfxConsoleInit(gfxPrintConsole* console, BgType type, BgSize size, bool mainDisplay, bool loadGraphics);

/*! \fn gfxPrintConsole* gfxConsoleDemoInit(void)
\brief Initialize the console to a default state for prototyping.
This function sets the console to use sub display, VRAM_C, and BG0 and enables MODE_5_2D on the
sub display.  It is intended for use in prototyping applications which need print ability and not actual
game use.  Print functionality can be utilized with just this call.  
*/
gfxPrintConsole* gfxConsoleDemoInit(void);

/*! \fn void gfxConsoleClear(void)
\brief Clears the screan by iprintf("\x1b[2J");
*/
void gfxConsoleClear(void);

/*! \fn void gfxConsoleDebugInit(DebugDevice device)
	\brief Initializes debug console output on stderr to the specified device
	\param device The debug device (or devices) to output debug print statements to
*/
void gfxConsoleDebugInit(DebugDevice device);

#ifdef __cplusplus
}
#endif

#endif
