#ifndef __BMFFONT_H__
#define __BMFFONT_H__

#include <nds.h>

/*! \file ByteMapFont.h
    \brief ByteMap Font helper structures and functions.

<div class="fileHeader">
Provides basic assistance to access ByteMap Font (BMF) files, these can be downloaded from http://bmf.wz.cz

</div>

*/

/**
 * \struct BMFRGB
 * \brief Basic RGB layout within the BMF files
 The font palette entries are in the range 0-63, these are bit shifted down when drawing the font.
 */

typedef struct 
{
	u8 bRed;
	u8 bGreen;
	u8 bBlue;
} BMFRGB;

/**
 * \struct BMFHeader
 * \brief The main header of the font files
There is a couple of items after these fields, these are:
<ul>
<li>Font palette - one BMFRGB entry for each palette entry, except palette 0
<li>Info length, the length of the information string
<li>Information string - normally the font name, and any other information the author wanted to add
<li>The number of characters in the file
<li>Font data using the BMFLetter structure
</ul>
 */

typedef struct
{
	u8 bMagic[4];	/*!< Magic number / file identifier it should be (in hex): E1 E6 D5 1A */
	u8 bVersion;	/*!< The version number of the file format, currently 11h */
	u8 bLineHeight;	/*!< The line height of the font */
	s8 bSizeOver;	/*!< The size-over the base line - (-128 - 127) */
	s8 bSizeUnder;	/*!< The size-under the base line - (-128 - 127) */
	s8 bAddSpace;	/*!< The amount of space to add after each character - (-128 - 127) */
	s8 bSizeInner;	/*!< Inner size / non capital size - (-128 - 127) */
	u8 bColours;	/*!< Number of colours in the font (maximum of 32 */
	u8 bHighPal;	/*!< Highest color used */
	u8 Reserved[4];	/*!< Reserved */
	u8 bPal;		/*!< Number of RGB entries */
} BMFHeader;

/**
 * \struct BMFLetter
 * \brief The header for each letter in the font
The byte preceding the first attribute is the letter that the header is for, this is not needed to be stored due to the way the BMFont structure is setup.
 */
typedef struct 
{
	u8 bWidth;	/*!< Width of the font */
	u8 bHeight;	/*!< Height of the font */
	s8 bRelX;	/*!< Horizontal offset according to cursor (-128 - 127) */
	s8 bRelY;	/*!< Vertical offset according to cursor (-128 - 127) */
	u8 bShift;	/*!< Horizontal cursor shift after drawing the font */
	u8 bData[];	/*!< The actual font data stored in 1 byte per pixel format */
} BMFLetter;

typedef struct 
{
	BMFHeader	*Head;	/*!< A pointer to the header of the file */
	BMFRGB		*pal;	/*!< A pointer to the first palette entry */
	u16		 wChars;	/*!< The number of characters in the font data */
	BMFLetter	*Ltrs[256];	/*!< A list of pointer to the actual letter data, if the pointer is NULL then that font is not part of this font file */
} BMFont;

#ifdef __cplusplus
extern "C" {
#endif

void LoadBMFont( BMFont *Fnt, const u8 *data );
void bmfPutCharTransparent( BMFont *Fnt, u8 x, u8 y, u16 text, u16 back, u16* Buffer, u8 Ltr );
void bmfPutCharOpaque( BMFont *Fnt, u8 x, u8 y, u16 text, u16 back, u16* Buffer, u8 Ltr );
u16 bmfColorIntensityBold( u16 color );
u16 bmfColorIntensityFaint( u16 color );

#ifdef __cplusplus
}
#endif

#endif