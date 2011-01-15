#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include <vector>
using namespace std;

// base object class
class Object
{
private:
	D3DXVECTOR3			m_vPos;			// position of the object on the screen
	float				m_fScale;		// how big the object is scaled
	float				m_fAngle;		// rotation
	D3DXMATRIX			m_mWorld;		// world transform
	D3DXVECTOR3			m_vCenter;
	D3DCOLOR			m_dColor;
	LPDIRECT3DTEXTURE9	m_lpTexture;


	// used for bounding and collision
	float				m_fLen;
	float				m_fWid;

public:
	Object();
	virtual void Update() = 0;

};

typedef vector<Object*> ObjectList;


#endif