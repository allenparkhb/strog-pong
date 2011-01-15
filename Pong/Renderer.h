#ifndef RENDERER_H
#define RENDERER_H

#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include <dxerr.h>
#pragma comment(lib, "dxerr.lib")
#include "FontHandler.h"


// graphics engine
class Renderer
{
private:
	IDirect3DDevice9*		m_pD3DDevice;		// the main d3d interface
	ID3DXFont*				m_pD3DFont;			// font used for fps display
	ID3DXSprite*			m_pD3DSprite;		// sprite used for the many models used in the game
	LPDIRECT3DTEXTURE9		m_lpTexture;		// texture that the above sprite uses
	D3DXIMAGE_INFO			m_imageInfo;		// image info that the above sprite uses
	HWND					m_hWnd;				// a 'personal' copy of the hWnd that Renderer can use
	bool					m_bWindowed;		// true = windowed; false = fullscreen
	float					m_fScreenWidth;		// screen height given by hWnd
	float					m_fScreenHeight;	// screen width given by hWnd
	D3DPRESENT_PARAMETERS	m_D3Dpp;			// present parameters
	
	FontHandler				Font;				// takes care of all font displays on the screen

	// used as temporary constructs to hold transform data
	D3DXMATRIX matRotation;
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;

	//private functions, called in Renderer::Init()
	void SetupDevice(HWND hWnd);
	void SetupFont();
	void SetupSpriteHandler();

public:
	Renderer();												// constructor that initializes most member variables to default values
	inline static Renderer* Instance()						// the instance of the singleton Renderer
	{
		static Renderer theRenderer;
		return &theRenderer;
	}
	void Init(HWND hWnd);									// initializes all systems of the class
	void Update();											// updates fps counter and sprite rotation
	void RenderOneFrame();									// renders one frame onto the screen
	D3DXIMAGE_INFO getSpriteImgInfo() {return m_imageInfo;}	// returns m_imageInfo so that sprites can be set up in main
	~Renderer();											// releases memory
};

#endif