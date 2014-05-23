#include "ByteMapFont.h"

void LoadBMFont( BMFont *Fnt, const u8 *data )
{
	u16 bCount;
	u32 lOffset;
	u8  bChar;
	
	if( ( Fnt ) && ( data ) )
	{
		Fnt->Head = (BMFHeader *) data;
		
		Fnt->pal = (BMFRGB *) &data[ 17 ];
		
		lOffset = 17 + ( Fnt->Head->bPal * 3 );
		
		lOffset += data[ lOffset ] + 1;
		
		Fnt->wChars = data[ lOffset ] + ( data[ lOffset + 1 ] << 8 );
		
		lOffset += 2;
		
		for( bCount = 0; bCount < 256; bCount ++ )
		{
			Fnt->Ltrs[ bCount ] = 0;
		}
		
		for( bCount = 0; bCount < Fnt->wChars; bCount ++ )
		{
			bChar = data[ lOffset ];
			
			Fnt->Ltrs[ bChar ] = (BMFLetter *) &data[ lOffset + 1 ];
			
			lOffset += 6 + ( Fnt->Ltrs[ bChar ]->bWidth * Fnt->Ltrs[ bChar ]->bHeight );
		}
		
		// echo hack - fix wide spacing of some fonts
		//Fnt->Ltrs[32]->bShift = 2;
	}
}

// Make the color bolder - basically makes the color twice as bright
u16 bmfColorIntensityBold( u16 color )
{
	u32 tcolor;
	
	tcolor = ( color  | ( color  << 16 ) ) & 0x03E07C1F;
	tcolor <<= 1;
	tcolor += 0x00200401;
	if( tcolor & 0x00000020 ) tcolor |= 0x0000001F;
	if( tcolor & 0x00008000 ) tcolor |= 0x00007C00;
	if( tcolor & 0x04000000 ) tcolor |= 0x03E00000;
	return ( tcolor | ( tcolor >> 16 ) ) & 0xFFFF;
}

// Make the color fainter - basically makes the color duller by reducing the intensity by 2
u16 bmfColorIntensityFaint( u16 color )
{
	u32 tcolor;
	
	tcolor = ( color  | ( color  << 16 ) ) & 0x03E07C1F;
	tcolor >>= 1;
//	tcolor += 0x00200401;
//	if( tcolor & 0x00000020 ) tcolor |= 0x0000001F;
//	if( tcolor & 0x00008000 ) tcolor |= 0x00007C00;
//	if( tcolor & 0x04000000 ) tcolor |= 0x03E00000;
	return ( tcolor | ( tcolor >> 16 ) ) & 0xFFFF;
}


void bmfPutCharTransparent( BMFont *Fnt, u8 x, u8 y, u16 text, u16 back, u16* Buffer, u8 Ltr )
{
	u8 i, j;
	u16 *Offset;
	u16 col;
	u8 bRed, bGreen, bBlue, bPal;
	
	if( Fnt->Ltrs[ Ltr ] )
	{
		Offset = Buffer + ( ( y + Fnt->Ltrs[ Ltr ]->bRelY ) << 8 );
		
		for( i = 0; i < Fnt->Ltrs[ Ltr ]->bHeight; i ++ )
		{
			for( j = 0; j < Fnt->Ltrs[ Ltr ]->bWidth; j ++ )
			{
				bPal = Fnt->Ltrs[ Ltr ]->bData[ j + ( i * Fnt->Ltrs[ Ltr ]->bWidth ) ];
				
				if( bPal > 0 )
				{
					bPal --;
					
					bRed = Fnt->pal[   bPal ].bRed >> 1;
					bGreen = Fnt->pal[ bPal ].bGreen >> 1;
					bBlue = Fnt->pal[  bPal ].bBlue >> 1;
					
					col = RGB5( bRed, bGreen, bBlue ) & text;
					
					Offset[ x + j + Fnt->Ltrs[ Ltr ]->bRelX ] = col | BIT(15);
				}
			}
			
			Offset += 256;
		}
	}
}

void bmfPutCharOpaque( BMFont *Fnt, u8 x, u8 y, u16 text, u16 back, u16* Buffer, u8 Ltr )
{
	s8 i, j;
	u16 *Offset;
	u16 col;
	u8 bRed, bGreen, bBlue, bPal;
	s8 bHeight, bWidth, bXOff, bYOff;
	u8 *bDataOffset;
	
	if( Fnt->Ltrs[ Ltr ] )
	{
		bDataOffset = Fnt->Ltrs[ Ltr ]->bData;
		
		bWidth  = Fnt->Ltrs[ Ltr ]->bShift;
		bHeight = Fnt->Head->bLineHeight;
		bXOff   = Fnt->Ltrs[ Ltr ]->bRelX;
		bYOff   = Fnt->Ltrs[ Ltr ]->bRelY;
		
		Offset = Buffer + ( y << 8 );
		
		for( i = 0; i <= bHeight; i ++ )
		{
			if( i < bYOff )
			{
				for( j = 0; j < bWidth + Fnt->Head->bAddSpace; j ++ )
				{
					Offset[ x + j ] = back;
				}
			}
			
			if( ( i >= bYOff ) && ( i < bYOff + Fnt->Ltrs[ Ltr ]->bHeight ) )
			{
				for( j = 0; j <= bXOff; j ++ )
					Offset[ x + j ] = back;
				
				for( j = 0; j < Fnt->Ltrs[ Ltr ]->bWidth; j ++ )
				{
					bPal = *bDataOffset;
					
					bDataOffset ++;
					
					bRed = Fnt->pal[   bPal - 1 ].bRed >> 1;
					bGreen = Fnt->pal[ bPal - 1 ].bGreen >> 1;
					bBlue = Fnt->pal[  bPal - 1 ].bBlue >> 1;
					
					col = (RGB15( bRed, bGreen, bBlue ) & text) | BIT(15);
					
					if( bPal == 0 ) // Normally transparent color
						col = back;
					
					Offset[ x + j + Fnt->Ltrs[ Ltr ]->bRelX ] = col;
				}
				
				for( j = Fnt->Ltrs[ Ltr ]->bWidth + bXOff; j < Fnt->Ltrs[ Ltr ]->bShift + Fnt->Head->bAddSpace; j ++ )
					Offset[ x + j ] = back;
			}
			
			if( i >= bYOff + Fnt->Ltrs[ Ltr ]->bHeight )
			{
				for( j = 0; j < Fnt->Ltrs[ Ltr ]->bShift + Fnt->Head->bAddSpace; j ++ )
				{
					Offset[ x + j ] = back;
				}
			}
			
			Offset += 256;
		}

/*		for( i = 0; i < Fnt->Head->bLineHeight; i ++ )
		{
			Offset = Buffer + ( ( y + i + Fnt->Ltrs[ Ltr ]->bRelY ) << 8 );
			for( j = 0; j < Fnt->Ltrs[ Ltr ]->bWidth; j ++ )
			{
				bPal = Fnt->Ltrs[ Ltr ]->bData[ j + ( i * Fnt->Ltrs[ Ltr ]->bWidth ) ];
				
				if( bPal > 0 )
				{
					bPal --;
					
					bRed = Fnt->pal[   bPal ].bRed >> 1;
					bGreen = Fnt->pal[ bPal ].bGreen >> 1;
					bBlue = Fnt->pal[  bPal ].bBlue >> 1;
					
					col = RGB5( bRed, bGreen, bBlue ) & text;
				}
				else
				{
					col = back;
				}
				
				Offset[ x + j + Fnt->Ltrs[ Ltr ]->bRelX ] = col | BIT(15);
			}
		}
*/	}

}
