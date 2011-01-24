#include "Ball.h"

void Ball::Init(int loc, ScreenDim dimensions)
{

	m_fScale = .15f;

	// obtain the ball texture
	m_tPack = Renderer::Instance()->getTexturePack(BALL);

	m_vCenter.x = m_tPack.imgInfo.Width * 0.5f * m_fScale;
	m_vCenter.y = m_tPack.imgInfo.Height * 0.5f * m_fScale;

	m_vStartPos.x = dimensions.width / 2 - m_vCenter.x;
	m_vStartPos.y = dimensions.height / 2 - m_vCenter.y;

	m_vPos = m_vStartPos;

	m_BoundingRect.top = (LONG)(m_vPos.y);
	m_BoundingRect.bottom = (LONG)(m_vPos.y + (m_tPack.imgInfo.Height * m_fScale));
	m_BoundingRect.left = (LONG)(m_vPos.x);
	m_BoundingRect.right = (LONG)(m_vPos.x + (m_tPack.imgInfo.Width * m_fScale));

	// the ball will initially travel up and left
	m_vDirection.x = -1;
	m_vDirection.y = 1;
	m_vDirection.z = 0;
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);
	m_speed = 0;
	m_vVelocity = m_vDirection * (float)m_speed;

	m_vOldPos = m_vPos;

	eType = BALL;
}

void Ball::Update()
{
	m_vOldPos = m_vPos;

	// if the ball is not moving, check for mouse click to start
	if(m_speed == 0)
	{
		if(DirectInput::Ins()->mouseButtonDown(0))
		{
			m_speed = 10;
			m_vVelocity = m_vDirection * (float)m_speed;
		}
	}
	m_vPos = m_vPos + m_vVelocity;		// update the position using velocity

	// update the bounding rect if the position has changed
	if(m_vOldPos.y != m_vPos.y)
	{
		m_BoundingRect.top = (LONG)(m_vPos.y);
		m_BoundingRect.bottom = (LONG)(m_vPos.y + (m_tPack.imgInfo.Height * m_fScale));
		m_BoundingRect.left = (LONG)(m_vPos.x);
		m_BoundingRect.right = (LONG)(m_vPos.x + (m_tPack.imgInfo.Width * m_fScale));
	}

}

void Ball::MoveBack()
{
	m_vOldPos = m_vPos;
}

void Ball::Bounce(int type)
{
	// invert either the x or y velocity, depending on how it collided
	if(type == WALL)
		m_vVelocity.y *= -1;
	if(type == PADDLE)
		m_vVelocity.x *= -1;
}

void Ball::setBack()
{
	m_vPos = m_vStartPos;							// reset the ball's position to the center
	m_speed = 0;									// set the speed to 0
	m_vVelocity = m_vDirection * (float)m_speed;	// reload velocity with new speed

	m_BoundingRect.top = (LONG)(m_vPos.y);
	m_BoundingRect.bottom = (LONG)(m_vPos.y + (m_tPack.imgInfo.Height * m_fScale));
	m_BoundingRect.left = (LONG)(m_vPos.x);
	m_BoundingRect.right = (LONG)(m_vPos.x + (m_tPack.imgInfo.Width * m_fScale));
}


