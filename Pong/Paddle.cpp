#include "Paddle.h"


void Paddle::Init(int xPos, int yPos, char up, char down)
{
	Wall::Init(xPos, yPos);
	m_tPack = Renderer::Instance()->getTexturePack(PADDLE);

	this->m_upKey = up;
	this->m_downKey = down;

	m_upperLimit = 0;
	m_lowerLimit = cnScreenHeight;
	m_speed = 5;
}


void Paddle::Update()
{
	if(DirectInput::Instance()->keyDown(m_upKey))
	{
		if(m_vPos.y + m_speed > m_upperLimit)
			m_vPos.y -= m_speed;
	}

	if(DirectInput::Instance()->keyDown(m_downKey))
	{
		if(m_vPos.y + m_speed < m_lowerLimit)
			m_vPos.y += m_speed;
	}
}