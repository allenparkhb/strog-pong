#include "FontHandler.h"

FontHandler::FontHandler()
	: m_pD3DFont(NULL)
	, m_fpsFontSize(30)
	, m_fps(0)
	, m_frameCount(0)
{
	m_oldTime = time(NULL);	// grabs initial time in seconds
}

void FontHandler::Init(ID3DXFont* pFont)
{
	this->m_pD3DFont = pFont;

	m_oss << "FPS: " << m_fps << "    ";

	SetRect(&m_fpsRect, 0, 0, m_fpsFontSize * m_oss.str().size(), m_fpsFontSize);	
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

void FontHandler::Draw()
{
	m_oss << "FPS: " << m_fps;

	m_pD3DFont->DrawTextA(NULL, m_oss.str().c_str(), m_oss.str().size(), &m_fpsRect, DT_LEFT | DT_NOCLIP, 
							D3DCOLOR_ARGB(255, 255, 255, 255));

	m_oss.clear();
	m_oss.str("");

	m_frameCount++;
}

FontHandler::~FontHandler()
{
	m_pD3DFont->Release();
}