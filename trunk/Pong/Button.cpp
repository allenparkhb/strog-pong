#include "Button.h"

void Button::Init(int loc, ScreenDim dimensions, int texture1, int texture2)
{
	top = 200;
	m_tPack = Renderer::Instance()->getTexturePack(texture1);
	m_tPack2 = Renderer::Instance()->getTexturePack(texture2);
	displayTexture = m_tPack;

	m_vPos.x = ((float)dimensions.width * 0.5f) - (m_tPack.imgInfo.Width * 0.5f);

	type = (eButton)loc;
	spacing = 30;

	// determines y position based on location enum
	switch(loc)
	{
	case PLAYBUTTON:
		m_vPos.y = top;
		break;
	case OPTIONSBUTTON:
		m_vPos.y = float(top + m_tPack.imgInfo.Height + spacing);
		break;
	case CREDITSBUTTON:
		m_vPos.y = float(top + (m_tPack.imgInfo.Height * 2.0f) + (spacing * 2.0f));
		break;
	case QUITBUTTON:
		m_vPos.y = float(top + (m_tPack.imgInfo.Height * 3.0f) + (spacing * 3.0f));
		break;
	}

	m_BoundingRect.top = (LONG)(m_vPos.y);
	m_BoundingRect.bottom = (LONG)(m_vPos.y + m_tPack.imgInfo.Height);
	m_BoundingRect.left = (LONG)(m_vPos.x);
	m_BoundingRect.right = (LONG)(m_vPos.x + m_tPack.imgInfo.Width);
}

void Button::ChangeTextures()
{
	if(displayTexture == m_tPack)
		displayTexture = m_tPack2;
	else
		displayTexture = m_tPack;
}