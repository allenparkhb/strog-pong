#ifndef FONTHANDLER_H
#define FONTHANDLER_H

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <sstream>
#include <ctime>
using namespace std;

#include "Usefuls.h"

class FontHandler
{
private:
	ID3DXFont*			m_pD3DFont;
	ostringstream		m_oss;				// used for displaying the fps in an acceptable format
	int					m_FontSize;			// size of the font for the fps counter
	// fps related variables
	RECT					m_fpsRect;			// rect that the fps font will be held in
	float					m_fps;				// holds the most recently recorded fps
	int						m_frameCount;		// frame counter
	time_t					m_newTime;			// most recent time in seconds
	time_t					m_oldTime;			// represents the last most recent time before newTime

	// score related variables
	int						m_score1;
	int						m_score2;
	RECT					m_s1Rect;
	RECT					m_s2Rect;

public:
	FontHandler();
	void Init(ID3DXFont* pFont, ScreenDim dims);
	void Update();
	void Draw(int, int);
	~FontHandler();

	//set/get functions
	int getFontSize() { return m_FontSize; }
};

#endif