#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include <vector>
using namespace std;
#include "Usefuls.h"

// base object class
class Object
{
protected:
	D3DXVECTOR3			m_vOldPos;		// old position used if needed to move back in case of collision
	D3DXVECTOR3			m_vPos;			// position of the object on the screen
	float				m_fScale;		// how big the object is scaled
	float				m_fAngle;		// rotation
	//D3DXMATRIX		m_mWorld;		// world transform
	D3DCOLOR			m_dColor;		// currently not being used
	TexturePack			m_tPack;		// holds the texture and image info
	D3DXVECTOR3			m_vCenter;		// center of the texture image


public:

	RECT				m_BoundingRect;	// used for collision
	int					eType;			// used for collision

	Object();
	virtual void Init(int loc, ScreenDim dimensions) = 0;
	virtual void Update() = 0;
	virtual void MoveBack() = 0;
	virtual void Bounce(int otherObject){}
	virtual void setBack(){}

	D3DXVECTOR3 getPosition() { return m_vPos; }
	float getScale() { return m_fScale; }
	float getAngle() { return m_fAngle; }

	D3DXVECTOR3 getCenter() { return m_vCenter; }
	LPDIRECT3DTEXTURE9 getTexture() { return m_tPack.lpTexture; }
	D3DXIMAGE_INFO getImgInfo() { return m_tPack.imgInfo; }
	RECT getBounding() { return m_BoundingRect; }
	void setWorld(D3DXMATRIX world);

};

#include "Renderer.h"



