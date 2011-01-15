#include "Object.h"

Object::Object()
	: m_vPos(0, 0, 0)
	, m_fScale(1)
	, m_fAngle(0)
	, m_vCenter(0, 0, 0)
	, m_fLen(0)
	, m_fWid(0)
{
	D3DXMatrixIdentity(&m_mWorld);
}

