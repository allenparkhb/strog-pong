#include "Wall.h"

void Wall::Init(int xPos, int yPos)
{
	m_tPack = Renderer::Instance()->getTexturePack(WALL);
	m_vPos.x = (float)xPos;
	m_vPos.y = (float)yPos;

	m_vCenter.x = m_tPack.imgInfo.Width * 0.5f;
	m_vCenter.y = m_tPack.imgInfo.Height * 0.5f;

	// setup the bounding rectangle based on the texture dimensions
	m_BoundingRect.top = (LONG)(m_vPos.y - m_vCenter.y);
	m_BoundingRect.bottom = (LONG)(m_vPos.y + m_vCenter.y);
	m_BoundingRect.left = (LONG)(m_vPos.x - m_vCenter.x);
	m_BoundingRect.right = (LONG)(m_vPos.x + m_vCenter.x);
}
