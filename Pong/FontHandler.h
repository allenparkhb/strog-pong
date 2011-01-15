#ifndef FONTHANDLER_H
#define FONTHANDLER_H

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <sstream>
#include <ctime>
using namespace std;

class FontHandler
{
private:
	ID3DXFont*			m_pD3DFont;

	// fps related variables
	RECT					m_fpsRect;			// rect that the fps font will be held in
	int						m_fpsFontSize;		// size of the font for the fps counter
	ostringstream			m_oss;				// used for displaying the fps in an acceptable format
	float					m_fps;				// holds the most recently recorded fps
	int						m_frameCount;		// frame counter
	time_t					m_newTime;			// most recent time in seconds
	time_t					m_oldTime;			// represents the last most recent time before newTime

public:
	FontHandler();
	void Init(ID3DXFont* pFont);
	void Update();
	void Draw();
	~FontHandler();

	//set/get functions
	int getFontSize() { return m_fpsFontSize; }
};

#endif