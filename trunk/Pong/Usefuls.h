#ifndef USEFULS_H
#define USEFULS_H

static const unsigned int cnObjectNum = 5;

enum eTextures
{
	WALL,
	PADDLE,
	BALL,
	TEXTURESIZE
};

enum ePositions
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct TexturePack
{
	LPDIRECT3DTEXTURE9	lpTexture;
	D3DXIMAGE_INFO		imgInfo;
};

struct ScreenDim
{
	unsigned int width;
	unsigned int height;
};

#endif