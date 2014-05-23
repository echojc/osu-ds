#include <nds.h>
#include "GfxInfo.h"

/*
const float zvalue[] = 
{
	0.000f, 0.000f, -0.01f, //hitcircle
	0.000f, 0.000f, 0.000f, //hitspinner
	-0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, //slider ball
	0.015f, -0.01f, 0.000f, 0.000f, //hitslider
	0.000f, 0.000f, 0.000f, 0.000f, 0.000f, 0.000f, 0.000f, //score
	-0.005f, -0.005f, //slider score
	-0.05f, -0.05f, -0.05f, -0.05f, -0.05f, //scorebar
	0.000f, //verdana9
	0.000f //white
};
*/

const u16 palette0[] = //circle, circleoverlay, circleapproach, disc, slidertick, sliderreverse, verdana9, white
{
	RGB15(31,0,31), RGB15(31,31,31), RGB15(28,28,28), RGB15(0,0,0)
};

const u16 palette1[] = //spinner, spinnerbars, scorebar_bar
{
	RGB15(31,31,31), RGB15(31,0,0), RGB15(31,4,0), RGB15(31,9,0), 
	RGB15(4,3,3), RGB15(29,14,7), RGB15(31,12,0), RGB15(31,17,0), 
	RGB15(31,23,7), RGB15(31,26,14), RGB15(31,23,0), RGB15(31,30,23), 
	RGB15(31,27,0), RGB15(31,31,8), RGB15(31,31,0), RGB15(0,14,22)
};

const u16 palette2[] = //spinnerbg
{
	RGB15(31,31,31), RGB15(1,2,5), RGB15(5,5,5), RGB15(0,0,0), 
	RGB15(5,13,31), RGB15(14,15,16), RGB15(2,5,13), RGB15(1,4,10), 
	RGB15(3,7,17), RGB15(3,8,21), RGB15(4,10,25), RGB15(1,3,8), 
	RGB15(5,11,28), RGB15(6,7,7), RGB15(4,5,8), RGB15(8,9,11)
};

const u16 palette3[] = //sliderball, sliderfollowcircle
{
	RGB15(31,0,31), RGB15(31,24,0), RGB15(31,0,0), RGB15(31,31,0)
};

const u16 palette4[] = //hit300, hit300k, hit300g, hit0
{
	RGB15(31,0,31), RGB15(31,26,4), RGB15(30,18,1), RGB15(31,30,12),
	RGB15(31,31,23), RGB15(9,6,4), RGB15(28,5,1), RGB15(3,3,4),
	RGB15(1,1,1), RGB15(2,2,2), RGB15(5,4,4), RGB15(28,2,2),
	RGB15(15,7,3), RGB15(13,13,10), RGB15(22,22,17), RGB15(21,17,4)
};

const u16 palette5[] = //hit50. hit100, hit100k
{
	RGB15(31,0,31), RGB15(3,3,4), RGB15(12,30,8), RGB15(4,10,3),
	RGB15(7,25,3), RGB15(12,15,28), RGB15(19,31,16), RGB15(5,6,11),
	RGB15(17,20,30), RGB15(6,9,23), RGB15(5,18,3), RGB15(23,24,29),
	RGB15(28,30,29), RGB15(24,31,23), RGB15(12,13,13), RGB15(18,19,19)
};

const u16 palette6[] = //slider30, slider10
{
	RGB15(31,0,31), RGB15(31,7,29), RGB15(0,0,0), RGB15(31,20,30)
};

const u16 palette7[] = //scorebar_ki, scorebar_kidanger, scorebar_kidanger2
{
	RGB15(31,31,31), RGB15(1,0,0), RGB15(20,20,20), RGB15(10,0,0), 
	RGB15(27,0,0), RGB15(20,0,0), RGB15(7,8,4), RGB15(12,12,0), 
	RGB15(22,23,9), RGB15(16,17,0), RGB15(20,21,0), RGB15(31,31,9), 
	RGB15(24,24,0), RGB15(30,31,1), RGB15(27,28,1), RGB15(16,16,6)
};

const u16 palette8[] = //scorebar
{
	RGB15(31,31,31), RGB15(0,0,0), RGB15(10,17,31), RGB15(19,17,31), 
	RGB15(21,23,31), RGB15(11,11,12), RGB15(17,17,31), RGB15(14,19,31), 
	RGB15(5,5,6), RGB15(18,18,31), RGB15(23,22,31), RGB15(20,18,31), 
	RGB15(16,19,31), RGB15(19,21,31), RGB15(14,14,18), RGB15(15,16,22)
};

const u32 uv8x8[] = {
	TEXTURE_PACK(inttot16(0),inttot16(0)),
	TEXTURE_PACK(inttot16(8), inttot16(0)),
	TEXTURE_PACK(inttot16(8),inttot16(8)),
	TEXTURE_PACK(inttot16(0), inttot16(8))
};

const u32 uv16x16[] = {
	TEXTURE_PACK(inttot16(0),inttot16(0)),
	TEXTURE_PACK(inttot16(16), inttot16(0)),
	TEXTURE_PACK(inttot16(16),inttot16(16)),
	TEXTURE_PACK(inttot16(0), inttot16(16))
};

const u32 uv32x32[] = {
	TEXTURE_PACK(inttot16(0),inttot16(0)),
	TEXTURE_PACK(inttot16(32), inttot16(0)),
	TEXTURE_PACK(inttot16(32),inttot16(32)),
	TEXTURE_PACK(inttot16(0), inttot16(32))
};

const u32 uv64x64[] = {
	TEXTURE_PACK(inttot16(0),inttot16(0)),
	TEXTURE_PACK(inttot16(64), 0),
	TEXTURE_PACK(inttot16(64),inttot16(64)),
	TEXTURE_PACK(inttot16(0), inttot16(64))
};

const u32 uv128x128[] = {
	TEXTURE_PACK(inttot16(0),inttot16(0)),
	TEXTURE_PACK(inttot16(128), inttot16(0)),
	TEXTURE_PACK(inttot16(128),inttot16(128)),
	TEXTURE_PACK(inttot16(0), inttot16(128))
};

const u32 uv256x16[] = {
	TEXTURE_PACK(inttot16(0),inttot16(0)),
	TEXTURE_PACK(inttot16(256), inttot16(0)),
	TEXTURE_PACK(inttot16(256),inttot16(16)),
	TEXTURE_PACK(inttot16(0), inttot16(16))
};

const u32 uv256x192[] = {
	TEXTURE_PACK(inttot16(0),inttot16(0)),
	TEXTURE_PACK(inttot16(256), inttot16(0)),
	TEXTURE_PACK(inttot16(256),inttot16(192)),
	TEXTURE_PACK(inttot16(0), inttot16(192))
};

const v16 plu[] = {
	floattov16(-2.00f),
	floattov16(-1.99f), floattov16(-1.98f), floattov16(-1.97f), floattov16(-1.96f), floattov16(-1.95f),
	floattov16(-1.94f), floattov16(-1.93f), floattov16(-1.92f), floattov16(-1.91f), floattov16(-1.90f),
	floattov16(-1.89f), floattov16(-1.88f), floattov16(-1.87f), floattov16(-1.86f), floattov16(-1.85f),
	floattov16(-1.84f), floattov16(-1.83f), floattov16(-1.82f), floattov16(-1.81f), floattov16(-1.80f),
	floattov16(-1.79f), floattov16(-1.78f), floattov16(-1.77f), floattov16(-1.76f), floattov16(-1.75f),
	floattov16(-1.74f), floattov16(-1.73f), floattov16(-1.72f), floattov16(-1.71f), floattov16(-1.70f),
	floattov16(-1.69f), floattov16(-1.68f), floattov16(-1.67f), floattov16(-1.66f), floattov16(-1.65f),
	floattov16(-1.64f), floattov16(-1.63f), floattov16(-1.62f), floattov16(-1.61f), floattov16(-1.60f),
	floattov16(-1.59f), floattov16(-1.58f), floattov16(-1.57f), floattov16(-1.56f), floattov16(-1.55f),
	floattov16(-1.54f), floattov16(-1.53f), floattov16(-1.52f), floattov16(-1.51f), floattov16(-1.50f),
	floattov16(-1.49f), floattov16(-1.48f), floattov16(-1.47f), floattov16(-1.46f), floattov16(-1.45f),
	floattov16(-1.44f), floattov16(-1.43f), floattov16(-1.42f), floattov16(-1.41f), floattov16(-1.40f),
	floattov16(-1.39f), floattov16(-1.38f), floattov16(-1.37f), floattov16(-1.36f), floattov16(-1.35f),
	floattov16(-1.34f), floattov16(-1.33f), floattov16(-1.32f), floattov16(-1.31f), floattov16(-1.30f),
	floattov16(-1.29f), floattov16(-1.28f), floattov16(-1.27f), floattov16(-1.26f), floattov16(-1.25f),
	floattov16(-1.24f), floattov16(-1.23f), floattov16(-1.22f), floattov16(-1.21f), floattov16(-1.20f),
	floattov16(-1.19f), floattov16(-1.18f), floattov16(-1.17f), floattov16(-1.16f), floattov16(-1.15f),
	floattov16(-1.14f), floattov16(-1.13f), floattov16(-1.12f), floattov16(-1.11f), floattov16(-1.10f),
	floattov16(-1.09f), floattov16(-1.08f), floattov16(-1.07f), floattov16(-1.06f), floattov16(-1.05f),
	floattov16(-1.04f), floattov16(-1.03f), floattov16(-1.02f), floattov16(-1.01f), floattov16(-1.00f),
	
	floattov16(-0.99f), floattov16(-0.98f), floattov16(-0.97f), floattov16(-0.96f), floattov16(-0.95f),
	floattov16(-0.94f), floattov16(-0.93f), floattov16(-0.92f), floattov16(-0.91f), floattov16(-0.90f),
	floattov16(-0.89f), floattov16(-0.88f), floattov16(-0.87f), floattov16(-0.86f), floattov16(-0.85f),
	floattov16(-0.84f), floattov16(-0.83f), floattov16(-0.82f), floattov16(-0.81f), floattov16(-0.80f),
	floattov16(-0.79f), floattov16(-0.78f), floattov16(-0.77f), floattov16(-0.76f), floattov16(-0.75f),
	floattov16(-0.74f), floattov16(-0.73f), floattov16(-0.72f), floattov16(-0.71f), floattov16(-0.70f),
	floattov16(-0.69f), floattov16(-0.68f), floattov16(-0.67f), floattov16(-0.66f), floattov16(-0.65f),
	floattov16(-0.64f), floattov16(-0.63f), floattov16(-0.62f), floattov16(-0.61f), floattov16(-0.60f),
	floattov16(-0.59f), floattov16(-0.58f), floattov16(-0.57f), floattov16(-0.56f), floattov16(-0.55f),
	floattov16(-0.54f), floattov16(-0.53f), floattov16(-0.52f), floattov16(-0.51f), floattov16(-0.50f),
	floattov16(-0.49f), floattov16(-0.48f), floattov16(-0.47f), floattov16(-0.46f), floattov16(-0.45f),
	floattov16(-0.44f), floattov16(-0.43f), floattov16(-0.42f), floattov16(-0.41f), floattov16(-0.40f),
	floattov16(-0.39f), floattov16(-0.38f), floattov16(-0.37f), floattov16(-0.36f), floattov16(-0.35f),
	floattov16(-0.34f), floattov16(-0.33f), floattov16(-0.32f), floattov16(-0.31f), floattov16(-0.30f),
	floattov16(-0.29f), floattov16(-0.28f), floattov16(-0.27f), floattov16(-0.26f), floattov16(-0.25f),
	floattov16(-0.24f), floattov16(-0.23f), floattov16(-0.22f), floattov16(-0.21f), floattov16(-0.20f),
	floattov16(-0.19f), floattov16(-0.18f), floattov16(-0.17f), floattov16(-0.16f), floattov16(-0.15f),
	floattov16(-0.14f), floattov16(-0.13f), floattov16(-0.12f), floattov16(-0.11f), floattov16(-0.10f),
	floattov16(-0.09f), floattov16(-0.08f), floattov16(-0.07f), floattov16(-0.06f), floattov16(-0.05f),
	floattov16(-0.04f), floattov16(-0.03f), floattov16(-0.02f), floattov16(-0.01f), 
	
	floattov16(0.00f), floattov16(0.01f), floattov16(0.02f), floattov16(0.03f), floattov16(0.04f),
	floattov16(0.05f), floattov16(0.06f), floattov16(0.07f), floattov16(0.08f), floattov16(0.09f),
	floattov16(0.10f), floattov16(0.11f), floattov16(0.12f), floattov16(0.13f), floattov16(0.14f),
	floattov16(0.15f), floattov16(0.16f), floattov16(0.17f), floattov16(0.18f), floattov16(0.19f),
	floattov16(0.20f), floattov16(0.21f), floattov16(0.22f), floattov16(0.23f), floattov16(0.24f),
	floattov16(0.25f), floattov16(0.26f), floattov16(0.27f), floattov16(0.28f), floattov16(0.29f),
	floattov16(0.30f), floattov16(0.31f), floattov16(0.32f), floattov16(0.33f), floattov16(0.34f),
	floattov16(0.35f), floattov16(0.36f), floattov16(0.37f), floattov16(0.38f), floattov16(0.39f),
	floattov16(0.40f), floattov16(0.41f), floattov16(0.42f), floattov16(0.43f), floattov16(0.44f),
	floattov16(0.45f), floattov16(0.46f), floattov16(0.47f), floattov16(0.48f), floattov16(0.49f),
	floattov16(0.50f), floattov16(0.51f), floattov16(0.52f), floattov16(0.53f), floattov16(0.54f),
	floattov16(0.55f), floattov16(0.56f), floattov16(0.57f), floattov16(0.58f), floattov16(0.59f),
	floattov16(0.60f), floattov16(0.61f), floattov16(0.62f), floattov16(0.63f), floattov16(0.64f),
	floattov16(0.65f), floattov16(0.66f), floattov16(0.67f), floattov16(0.68f), floattov16(0.69f),
	floattov16(0.70f), floattov16(0.71f), floattov16(0.72f), floattov16(0.73f), floattov16(0.74f),
	floattov16(0.75f), floattov16(0.76f), floattov16(0.77f), floattov16(0.78f), floattov16(0.79f),
	floattov16(0.80f), floattov16(0.81f), floattov16(0.82f), floattov16(0.83f), floattov16(0.84f),
	floattov16(0.85f), floattov16(0.86f), floattov16(0.87f), floattov16(0.88f), floattov16(0.89f),
	floattov16(0.90f), floattov16(0.91f), floattov16(0.92f), floattov16(0.93f), floattov16(0.94f),
	floattov16(0.95f), floattov16(0.96f), floattov16(0.97f), floattov16(0.98f), floattov16(0.99f),
	
	floattov16(1.00f), floattov16(1.01f), floattov16(1.02f), floattov16(1.03f), floattov16(1.04f),
	floattov16(1.05f), floattov16(1.06f), floattov16(1.07f), floattov16(1.08f), floattov16(1.09f),
	floattov16(1.10f), floattov16(1.11f), floattov16(1.12f), floattov16(1.13f), floattov16(1.14f),
	floattov16(1.15f), floattov16(1.16f), floattov16(1.17f), floattov16(1.18f), floattov16(1.19f),
	floattov16(1.20f), floattov16(1.21f), floattov16(1.22f), floattov16(1.23f), floattov16(1.24f),
	floattov16(1.25f), floattov16(1.26f), floattov16(1.27f), floattov16(1.28f), floattov16(1.29f),
	floattov16(1.30f), floattov16(1.31f), floattov16(1.32f), floattov16(1.33f), floattov16(1.34f),
	floattov16(1.35f), floattov16(1.36f), floattov16(1.37f), floattov16(1.38f), floattov16(1.39f),
	floattov16(1.40f), floattov16(1.41f), floattov16(1.42f), floattov16(1.43f), floattov16(1.44f),
	floattov16(1.45f), floattov16(1.46f), floattov16(1.47f), floattov16(1.48f), floattov16(1.49f),
	floattov16(1.50f), floattov16(1.51f), floattov16(1.52f), floattov16(1.53f), floattov16(1.54f),
	floattov16(1.55f), floattov16(1.56f), floattov16(1.57f), floattov16(1.58f), floattov16(1.59f),
	floattov16(1.60f), floattov16(1.61f), floattov16(1.62f), floattov16(1.63f), floattov16(1.64f),
	floattov16(1.65f), floattov16(1.66f), floattov16(1.67f), floattov16(1.68f), floattov16(1.69f),
	floattov16(1.70f), floattov16(1.71f), floattov16(1.72f), floattov16(1.73f), floattov16(1.74f),
	floattov16(1.75f), floattov16(1.76f), floattov16(1.77f), floattov16(1.78f), floattov16(1.79f),
	floattov16(1.80f), floattov16(1.81f), floattov16(1.82f), floattov16(1.83f), floattov16(1.84f),
	floattov16(1.85f), floattov16(1.86f), floattov16(1.87f), floattov16(1.88f), floattov16(1.89f),
	floattov16(1.90f), floattov16(1.91f), floattov16(1.92f), floattov16(1.93f), floattov16(1.94f),
	floattov16(1.95f), floattov16(1.96f), floattov16(1.97f), floattov16(1.98f), floattov16(1.99f),
	
	floattov16(2.00f), floattov16(2.01f), floattov16(2.02f), floattov16(2.03f), floattov16(2.04f),
	floattov16(2.05f), floattov16(2.06f), floattov16(2.07f), floattov16(2.08f), floattov16(2.09f),
	floattov16(2.10f), floattov16(2.11f), floattov16(2.12f), floattov16(2.13f), floattov16(2.14f),
	floattov16(2.15f), floattov16(2.16f), floattov16(2.17f), floattov16(2.18f), floattov16(2.19f),
	floattov16(2.20f), floattov16(2.21f), floattov16(2.22f), floattov16(2.23f), floattov16(2.24f),
	floattov16(2.25f), floattov16(2.26f), floattov16(2.27f), floattov16(2.28f), floattov16(2.29f),
	floattov16(2.30f), floattov16(2.31f), floattov16(2.32f), floattov16(2.33f), floattov16(2.34f),
	floattov16(2.35f), floattov16(2.36f), floattov16(2.37f), floattov16(2.38f), floattov16(2.39f),
	floattov16(2.40f), floattov16(2.41f), floattov16(2.42f), floattov16(2.43f), floattov16(2.44f),
	floattov16(2.45f), floattov16(2.46f), floattov16(2.47f), floattov16(2.48f), floattov16(2.49f),
	floattov16(2.50f), floattov16(2.51f), floattov16(2.52f), floattov16(2.53f), floattov16(2.54f),
	floattov16(2.55f), floattov16(2.56f), floattov16(2.57f), floattov16(2.58f), floattov16(2.59f),
	floattov16(2.60f), floattov16(2.61f), floattov16(2.62f), floattov16(2.63f), floattov16(2.64f),
	floattov16(2.65f), floattov16(2.66f), floattov16(2.67f), floattov16(2.68f), floattov16(2.69f),
	floattov16(2.70f), floattov16(2.71f), floattov16(2.72f), floattov16(2.73f), floattov16(2.74f),
	floattov16(2.75f), floattov16(2.76f), floattov16(2.77f), floattov16(2.78f), floattov16(2.79f),
	floattov16(2.80f), floattov16(2.81f), floattov16(2.82f), floattov16(2.83f), floattov16(2.84f),
	floattov16(2.85f), floattov16(2.86f), floattov16(2.87f), floattov16(2.88f), floattov16(2.89f),
	floattov16(2.90f), floattov16(2.91f), floattov16(2.92f), floattov16(2.93f), floattov16(2.94f),
	floattov16(2.95f), floattov16(2.96f), floattov16(2.97f), floattov16(2.98f), floattov16(2.99f),
	
	floattov16(3.00f), floattov16(3.01f), floattov16(3.02f), floattov16(3.03f), floattov16(3.04f),
	floattov16(3.05f), floattov16(3.06f), floattov16(3.07f), floattov16(3.08f), floattov16(3.09f),
	floattov16(3.10f), floattov16(3.11f), floattov16(3.12f), floattov16(3.13f), floattov16(3.14f),
	floattov16(3.15f), floattov16(3.16f), floattov16(3.17f), floattov16(3.18f), floattov16(3.19f),
	floattov16(3.20f), floattov16(3.21f), floattov16(3.22f), floattov16(3.23f), floattov16(3.24f),
	floattov16(3.25f), floattov16(3.26f), floattov16(3.27f), floattov16(3.28f), floattov16(3.29f),
	floattov16(3.30f), floattov16(3.31f), floattov16(3.32f), floattov16(3.33f), floattov16(3.34f),
	floattov16(3.35f), floattov16(3.36f), floattov16(3.37f), floattov16(3.38f), floattov16(3.39f),
	floattov16(3.40f), floattov16(3.41f), floattov16(3.42f), floattov16(3.43f), floattov16(3.44f),
	floattov16(3.45f), floattov16(3.46f), floattov16(3.47f), floattov16(3.48f), floattov16(3.49f),
	floattov16(3.50f), floattov16(3.51f), floattov16(3.52f), floattov16(3.53f), floattov16(3.54f),
	floattov16(3.55f), floattov16(3.56f), floattov16(3.57f), floattov16(3.58f), floattov16(3.59f),
	floattov16(3.60f), floattov16(3.61f), floattov16(3.62f), floattov16(3.63f), floattov16(3.64f),
	floattov16(3.65f), floattov16(3.66f), floattov16(3.67f), floattov16(3.68f), floattov16(3.69f),
	floattov16(3.70f), floattov16(3.71f), floattov16(3.72f), floattov16(3.73f), floattov16(3.74f),
	floattov16(3.75f), floattov16(3.76f), floattov16(3.77f), floattov16(3.78f), floattov16(3.79f),
	floattov16(3.80f), floattov16(3.81f), floattov16(3.82f), floattov16(3.83f), floattov16(3.84f),
	floattov16(3.85f), floattov16(3.86f), floattov16(3.87f), floattov16(3.88f), floattov16(3.89f),
	floattov16(3.90f), floattov16(3.91f), floattov16(3.92f), floattov16(3.93f), floattov16(3.94f),
	floattov16(3.95f), floattov16(3.96f), floattov16(3.97f), floattov16(3.98f), floattov16(3.99f),
	
	floattov16(4.00f), floattov16(4.01f), floattov16(4.02f), floattov16(4.03f), floattov16(4.04f),
	floattov16(4.05f), floattov16(4.06f), floattov16(4.07f), floattov16(4.08f), floattov16(4.09f),
	floattov16(4.10f), floattov16(4.11f), floattov16(4.12f), floattov16(4.13f), floattov16(4.14f),
	floattov16(4.15f), floattov16(4.16f), floattov16(4.17f), floattov16(4.18f), floattov16(4.19f),
	floattov16(4.20f), floattov16(4.21f), floattov16(4.22f), floattov16(4.23f), floattov16(4.24f),
	floattov16(4.25f), floattov16(4.26f), floattov16(4.27f), floattov16(4.28f), floattov16(4.29f),
	floattov16(4.30f), floattov16(4.31f), floattov16(4.32f), floattov16(4.33f), floattov16(4.34f),
	floattov16(4.35f), floattov16(4.36f), floattov16(4.37f), floattov16(4.38f), floattov16(4.39f),
	floattov16(4.40f), floattov16(4.41f), floattov16(4.42f), floattov16(4.43f), floattov16(4.44f),
	floattov16(4.45f), floattov16(4.46f), floattov16(4.47f), floattov16(4.48f), floattov16(4.49f),
	floattov16(4.50f), floattov16(4.51f), floattov16(4.52f), floattov16(4.53f), floattov16(4.54f),
	floattov16(4.55f), floattov16(4.56f), floattov16(4.57f), floattov16(4.58f), floattov16(4.59f),
	floattov16(4.60f), floattov16(4.61f), floattov16(4.62f), floattov16(4.63f), floattov16(4.64f),
	floattov16(4.65f), floattov16(4.66f), floattov16(4.67f), floattov16(4.68f), floattov16(4.69f),
	floattov16(4.70f), floattov16(4.71f), floattov16(4.72f), floattov16(4.73f), floattov16(4.74f),
	floattov16(4.75f), floattov16(4.76f), floattov16(4.77f), floattov16(4.78f), floattov16(4.79f),
	floattov16(4.80f), floattov16(4.81f), floattov16(4.82f), floattov16(4.83f), floattov16(4.84f),
	floattov16(4.85f), floattov16(4.86f), floattov16(4.87f), floattov16(4.88f), floattov16(4.89f),
	floattov16(4.90f), floattov16(4.91f), floattov16(4.92f), floattov16(4.93f), floattov16(4.94f),
	floattov16(4.95f), floattov16(4.96f), floattov16(4.97f), floattov16(4.98f), floattov16(4.99f),
	
	floattov16(5.00f), floattov16(5.01f), floattov16(5.02f), floattov16(5.03f), floattov16(5.04f),
	floattov16(5.05f), floattov16(5.06f), floattov16(5.07f), floattov16(5.08f), floattov16(5.09f),
	floattov16(5.10f), floattov16(5.11f), floattov16(5.12f), floattov16(5.13f), floattov16(5.14f),
	floattov16(5.15f), floattov16(5.16f), floattov16(5.17f), floattov16(5.18f), floattov16(5.19f),
	floattov16(5.20f), floattov16(5.21f), floattov16(5.22f), floattov16(5.23f), floattov16(5.24f),
	floattov16(5.25f), floattov16(5.26f), floattov16(5.27f), floattov16(5.28f), floattov16(5.29f),
	floattov16(5.30f), floattov16(5.31f), floattov16(5.32f), floattov16(5.33f), floattov16(5.34f),
	floattov16(5.35f), floattov16(5.36f), floattov16(5.37f), floattov16(5.38f), floattov16(5.39f),
	floattov16(5.40f), floattov16(5.41f), floattov16(5.42f), floattov16(5.43f), floattov16(5.44f),
	floattov16(5.45f), floattov16(5.46f), floattov16(5.47f), floattov16(5.48f), floattov16(5.49f),
	floattov16(5.50f), floattov16(5.51f), floattov16(5.52f), floattov16(5.53f), floattov16(5.54f),
	floattov16(5.55f), floattov16(5.56f), floattov16(5.57f), floattov16(5.58f), floattov16(5.59f),
	floattov16(5.60f), floattov16(5.61f), floattov16(5.62f), floattov16(5.63f), floattov16(5.64f),
	floattov16(5.65f), floattov16(5.66f), floattov16(5.67f), floattov16(5.68f), floattov16(5.69f),
	floattov16(5.70f), floattov16(5.71f), floattov16(5.72f), floattov16(5.73f), floattov16(5.74f),
	floattov16(5.75f), floattov16(5.76f), floattov16(5.77f), floattov16(5.78f), floattov16(5.79f),
	floattov16(5.80f), floattov16(5.81f), floattov16(5.82f), floattov16(5.83f), floattov16(5.84f),
	floattov16(5.85f), floattov16(5.86f), floattov16(5.87f), floattov16(5.88f), floattov16(5.89f),
	floattov16(5.90f), floattov16(5.91f), floattov16(5.92f), floattov16(5.93f), floattov16(5.94f),
	floattov16(5.95f), floattov16(5.96f), floattov16(5.97f), floattov16(5.98f), floattov16(5.99f),
	
	floattov16(6.00f), floattov16(6.01f), floattov16(6.02f), floattov16(6.03f), floattov16(6.04f),
	floattov16(6.05f), floattov16(6.06f), floattov16(6.07f), floattov16(6.08f), floattov16(6.09f),
	floattov16(6.10f), floattov16(6.11f), floattov16(6.12f), floattov16(6.13f), floattov16(6.14f),
	floattov16(6.15f), floattov16(6.16f), floattov16(6.17f), floattov16(6.18f), floattov16(6.19f),
	floattov16(6.20f), floattov16(6.21f), floattov16(6.22f), floattov16(6.23f), floattov16(6.24f),
	floattov16(6.25f), floattov16(6.26f), floattov16(6.27f), floattov16(6.28f), floattov16(6.29f),
	floattov16(6.30f), floattov16(6.31f), floattov16(6.32f), floattov16(6.33f), floattov16(6.34f),
	floattov16(6.35f), floattov16(6.36f), floattov16(6.37f), floattov16(6.38f), floattov16(6.39f),
	floattov16(6.40f), floattov16(6.41f), floattov16(6.42f), floattov16(6.43f), floattov16(6.44f),
	floattov16(6.45f), floattov16(6.46f), floattov16(6.47f), floattov16(6.48f), floattov16(6.49f),
	floattov16(6.50f), floattov16(6.51f), floattov16(6.52f), floattov16(6.53f), floattov16(6.54f),
	floattov16(6.55f), floattov16(6.56f), floattov16(6.57f), floattov16(6.58f), floattov16(6.59f),
	floattov16(6.60f), floattov16(6.61f), floattov16(6.62f), floattov16(6.63f), floattov16(6.64f),
	floattov16(6.65f), floattov16(6.66f), floattov16(6.67f), floattov16(6.68f), floattov16(6.69f),
	floattov16(6.70f), floattov16(6.71f), floattov16(6.72f), floattov16(6.73f), floattov16(6.74f),
	floattov16(6.75f), floattov16(6.76f), floattov16(6.77f), floattov16(6.78f), floattov16(6.79f),
	floattov16(6.80f), floattov16(6.81f), floattov16(6.82f), floattov16(6.83f), floattov16(6.84f),
	floattov16(6.85f), floattov16(6.86f), floattov16(6.87f), floattov16(6.88f), floattov16(6.89f),
	floattov16(6.90f), floattov16(6.91f), floattov16(6.92f), floattov16(6.93f), floattov16(6.94f),
	floattov16(6.95f), floattov16(6.96f), floattov16(6.97f), floattov16(6.98f), floattov16(6.99f),
	
	floattov16(7.00f), floattov16(7.01f), floattov16(7.02f), floattov16(7.03f), floattov16(7.04f),
	floattov16(7.05f), floattov16(7.06f), floattov16(7.07f), floattov16(7.08f), floattov16(7.09f),
	floattov16(7.10f), floattov16(7.11f), floattov16(7.12f), floattov16(7.13f), floattov16(7.14f),
	floattov16(7.15f), floattov16(7.16f), floattov16(7.17f), floattov16(7.18f), floattov16(7.19f),
	floattov16(7.20f), floattov16(7.21f), floattov16(7.22f), floattov16(7.23f), floattov16(7.24f),
	floattov16(7.25f), floattov16(7.26f), floattov16(7.27f), floattov16(7.28f), floattov16(7.29f),
	floattov16(7.30f), floattov16(7.31f), floattov16(7.32f), floattov16(7.33f), floattov16(7.34f),
	floattov16(7.35f), floattov16(7.36f), floattov16(7.37f), floattov16(7.38f), floattov16(7.39f),
	floattov16(7.40f), floattov16(7.41f), floattov16(7.42f), floattov16(7.43f), floattov16(7.44f),
	floattov16(7.45f), floattov16(7.46f), floattov16(7.47f), floattov16(7.48f), floattov16(7.49f),
	floattov16(7.50f), floattov16(7.51f), floattov16(7.52f), floattov16(7.53f), floattov16(7.54f),
	floattov16(7.55f), floattov16(7.56f), floattov16(7.57f), floattov16(7.58f), floattov16(7.59f),
	floattov16(7.60f), floattov16(7.61f), floattov16(7.62f), floattov16(7.63f), floattov16(7.64f),
	floattov16(7.65f), floattov16(7.66f), floattov16(7.67f), floattov16(7.68f), floattov16(7.69f),
	floattov16(7.70f), floattov16(7.71f), floattov16(7.72f), floattov16(7.73f), floattov16(7.74f),
	floattov16(7.75f), floattov16(7.76f), floattov16(7.77f), floattov16(7.78f), floattov16(7.79f),
	floattov16(7.80f), floattov16(7.81f), floattov16(7.82f), floattov16(7.83f), floattov16(7.84f),
	floattov16(7.85f), floattov16(7.86f), floattov16(7.87f), floattov16(7.88f), floattov16(7.89f),
	floattov16(7.90f), floattov16(7.91f), floattov16(7.92f), floattov16(7.93f), floattov16(7.94f),
	floattov16(7.95f), floattov16(7.96f), floattov16(7.97f), floattov16(7.98f), floattov16(7.99f)
};

