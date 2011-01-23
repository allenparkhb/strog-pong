#include "Paddle.h"


void Paddle::Init(int loc, char up, char down, ScreenDim dimensions)
{
	// obtain the paddle texture
	m_tPack = Renderer::Instance()->getTexturePack(PADDLE);

	score = 0;

	// set the y position of the paddle to be in the middle of the screen
	m_vPos.y = (float)(dimensions.height * 0.5f - (m_tPack.imgInfo.Height * 0.5f));

	if(loc == RIGHT)
	{
		m_vPos.x = (float)(dimensions.width - m_tPack.imgInfo.Width);	// set the x position for the right paddle
	}
	else
		m_vPos.x = 0;										// set the x position for the left paddle

	m_vCenter.x = m_tPack.imgInfo.Width * 0.5f;
	m_vCenter.y = m_tPack.imgInfo.Height * 0.5f;

	m_BoundingRect.top = (LONG)(m_vPos.y);
	m_BoundingRect.bottom = (LONG)(m_vPos.y + m_tPack.imgInfo.Height);
	m_BoundingRect.left = (LONG)(m_vPos.x);
	m_BoundingRect.right = (LONG)(m_vPos.x + m_tPack.imgInfo.Width);

	this->m_upKey = up;
	this->m_downKey = down;

	m_speed = 2;

	m_vOldPos = m_vPos;

	eType = PADDLE;
}


void Paddle::Update()
{
	m_vOldPos = m_vPos;

	if(DirectInput::Instance()->keyDown(m_upKey))
			m_vPos.y -= m_speed;

	if(DirectInput::Instance()->keyDown(m_downKey))
			m_vPos.y += m_speed;

	// update the bounding rect if the position has changed
	if(m_vOldPos.y != m_vPos.y)
	{
		m_BoundingRect.top = (LONG)(m_vPos.y);
		m_BoundingRect.bottom = (LONG)(m_vPos.y + m_tPack.imgInfo.Height);
		m_BoundingRect.left = (LONG)(m_vPos.x);
		m_BoundingRect.right = (LONG)(m_vPos.x + m_tPack.imgInfo.Width);
	}
}

void Paddle::MoveBack()
{
	m_vPos = m_vOldPos;
}