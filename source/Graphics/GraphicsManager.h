#include <nds.h>
#include <string.h>
#include <stdio.h>

#include "GfxInfo.h"

#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

//#define glVertex2lu(x,y) glVertex3v16(plu[(x)+200],plu[(y)+200],0)
//#define glVertex3lu(x,y,z) glVertex3v16(plu[(x)+200],plu[(y)+200],plu[(z)+200])
#define glVertex2lu1f(x,y,z) glVertex3v16(plu[(x)+200],plu[(y)+200],floattov16(z))

#define LoadGLTexture(tex, type, sizeX, sizeY, palette, uv, texture) \
			LoadGLTextureEx(tex, type, sizeX, sizeY, palette, uv, texture, texture##_size)

typedef struct {
	int palette;
	u8 format;
	const u32* uv;
} TextureInfo;

typedef enum {
	ORIGIN_CENTER,
	ORIGIN_TOPLEFT,
	ORIGIN_BOTTOMLEFT,
	ORIGIN_TOPRIGHT
} DrawOrigin;

typedef enum {
	FIELD_SCREEN,
	FIELD_PLAY
} FieldType;

class GraphicsManager
{
	public:
		static GraphicsManager& Graphics() { return sGraphicsManager; }
		
		void Draw(TextureType tex, s32 x, s32 y, u32 width, u32 height, DrawOrigin origin, FieldType fieldtype, rgb color, u32 alpha, s32 angle, float z = 0, const u32* uv = NULL);
		
		static const u32 PlayXOffset = 64;
		static const u32 PlayYOffset = 73;
	
	protected:
		void LoadGLTextureEx(TextureType tex, GL_TEXTURE_TYPE_ENUM type, int sizeX, int sizeY, int palette, const u32* uv, const u8* texture, u32 size);
		s32 ForceBounds(s32 value);
		
		TextureInfo textureInfo[NUMBER_OF_TEXTURES];
		int textures[NUMBER_OF_TEXTURES];
		
		static GraphicsManager sGraphicsManager;
	
	private:
		GraphicsManager();
		~GraphicsManager() {}
		
		u32 mPolygonId;
};

#endif

