#include "FontHandler.h"

FontHandler::FontHandler()
	: m_pD3DFont(NULL)
	, m_FontSize(30)
	, m_fps(0)
	, m_frameCount(0)
	, m_score1(0)
	, m_score2(0)
{
	m_oldTime = time(NULL);	// grabs initial time in seconds
}

void FontHandler::Init(ID3DXFont* pFont, ScreenDim dims)
{
	this->m_pD3DFont = pFont;

	m_oss << "FPS: " << m_fps << "    ";

	SetRect(&m_fpsRect, 0, 0, m_FontSize * m_oss.str().size(), m_FontSize);
	SetRect(&m_s1Rect, 0, dims.height - m_FontSize, m_FontSize, dims.height);
	SetRect(&m_s2Rect, dims.width - m_FontSize, dims. height - m_FontSize, dims.width, dims.height);
}

void FontHandler::Update()
{
	//update frames per second counter
	m_newTime = time(NULL);			// grab the new time

	if(m_newTime > m_oldTime)
	{
		m_fps = (float)m_frameCount;
		m_oldTime = m_newTime;
		m_frameCount = 0;
	}
}

void FontHandler::Draw(int s1, int s2)
{
	m_score1 = s1;
	m_score2 = s2;
	char* temp;
	temp = new char;
	m_oss << "FPS: " << m_fps;

	// draw the fps counter
	m_pD3DFont->DrawTextA(NULL, m_oss.str().c_str(), m_oss.str().size(), &m_fpsRect, DT_LEFT | DT_NOCLIP, 
							D3DCOLOR_ARGB(255, 255, 255, 255));

	// draw the scores
	m_pD3DFont->DrawTextA(NULL, _itoa(m_score1, temp, 10), 1, &m_s1Rect,
							DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pD3DFont->DrawTextA(NULL, _itoa(m_score2, temp, 10), 1, &m_s2Rect,
							DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_oss.clear();
	m_oss.str("");

	m_frameCount++;
}

FontHandler::~FontHandler()
{
	m_pD3DFont->Release();
}