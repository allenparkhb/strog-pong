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
	D3DXVECTOR3			m_vPos;			// position of the object on the screen
	float				m_fScale;		// how big the object is scaled
	float				m_fAngle;		// rotation
	//D3DXMATRIX		m_mWorld;		// world transform
	D3DCOLOR			m_dColor;
	TexturePack			m_tPack;
	D3DXVECTOR3			m_vCenter;
	RECT				m_BoundingRect;	// used for collision

public:

	Object();
	virtual void Init(int xPos, int yPos)   = 0;
	virtual void Update() = 0;
	D3DXVECTOR3 getPosition() { return m_vPos; }
	float getScale() { return m_fScale; }
	float getAngle() { return m_fAngle; }
	D3DXVECTOR3 getCenter() { return m_vCenter; }
	LPDIRECT3DTEXTURE9 getTexture() { return m_tPack.lpTexture; }
	void setWorld(D3DXMATRIX world);

};

typedef vector<Object*> ObjectList;

#include "Renderer.h"



