#pragma once

static const unsigned int cnScreenWidth = 800;
static const unsigned int cnScreenHeight = 600;

enum eTextures
{
	WALL,
	PADDLE,
	BALL,
	TEXTURESIZE
};

struct TexturePack
{
	LPDIRECT3DTEXTURE9	lpTexture;
	D3DXIMAGE_INFO		imgInfo;
};