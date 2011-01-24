#ifndef USEFULS_H
#define USEFULS_H

static const unsigned int cnObjectNum = 5;

enum eTextures
{
	WALL,
	PADDLE,
	BALL,

	// used for menu textures
	MAINMENU,
	PLAY_UNP,
	PLAY_P,
	OPTIONS_UNP,
	OPTIONS_P,
	CREDITS_UNP,
	CREDITS_P,
	CREDITSPAGE,	// the actual credits page, not to be confused with the credits button
	QUIT_UNP,
	QUIT_P,
	TEXTURESIZE
};

enum ePositions
{
	// game object positions
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	MIDDLE,

	//menu positions
	FIRST,
	SECOND,
	THIRD,
	FOURTH

};

enum eScoreState
{
	INPROGRESS,
	P1WINS,
	P2WINS
};

enum eButton
{
	PLAYBUTTON,
	OPTIONSBUTTON,
	CREDITSBUTTON,
	QUITBUTTON,
	NUMBUTTONS
};

enum eGameStates
{
	LOADING,
	INTRO,
	MENU,
	GAME,
	CREDITS,
	QUIT
};

enum eMenuStates
{
	MAINSTATE,
	OPTIONSTATE,
	CREDITSSTATE
};

struct TexturePack
{
	LPDIRECT3DTEXTURE9	lpTexture;
	D3DXIMAGE_INFO		imgInfo;

	bool operator==(TexturePack comparee)
	{
		if(this->lpTexture == comparee.lpTexture)
		{
			return true;
		}

		return false;
	}
};

struct ScreenDim
{
	unsigned int width;
	unsigned int height;
};

#endif