#include "Wall.h"

void Wall::Init(int loc, ScreenDim dimensions)
{
	// obtain the wall texture
	m_tPack = Renderer::Instance()->getTexturePack(WALL);

	
	m_vPos.x = 0;			// x position of walls is always 0

	if(loc == BOTTOM)		// set the bottom wall's y position
		m_vPos.y = (float)dimensions.height - m_tPack.imgInfo.Height;
	else
		m_vPos.y = 0;		// set the top wall's y position

	// the center of the image
	m_vCenter.x = m_tPack.imgInfo.Width * 0.5f;
	m_vCenter.y = m_tPack.imgInfo.Height * 0.5f;

	// setup the bounding rectangle based on the texture dimensions
	m_BoundingRect.top = (LONG)(m_vPos.y);
	m_BoundingRect.bottom = (LONG)(m_vPos.y + m_tPack.imgInfo.Height);
	m_BoundingRect.left = (LONG)(m_vPos.x);
	m_BoundingRect.right = (LONG)(m_vPos.x + m_tPack.imgInfo.Width);
}
