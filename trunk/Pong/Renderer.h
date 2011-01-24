#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include <dxerr.h>
#pragma comment(lib, "dxerr.lib")
#include "FontHandler.h"
#include "Object.h"
#include "ObjectList.h"
#include "Usefuls.h"
#include "Menu.h"

class ObjectList;

// graphics engine
class Renderer
{
	private:
	Renderer();										// as this is a singleton, the ctor is private

	IDirect3DDevice9*		m_pD3DDevice;			// the main d3d interface
	ID3DXFont*				m_pD3DFont;				// font used for fps display
	ID3DXSprite*			m_pD3DSprite;			// sprite used for the many models used in the game
	TexturePack				m_tPacks[TEXTURESIZE];	// array of texture and image_info
	char*					m_cszFiles[TEXTURESIZE];// array of texture file names
	HWND					m_hWnd;					// a 'personal' copy of the hWnd that Renderer can use
	bool					m_bWindowed;			// true = windowed; false = fullscreen
	ScreenDim				m_dimensions;			// screen height and width
	D3DPRESENT_PARAMETERS	m_D3Dpp;				// present parameters
	
	FontHandler				Font;					// takes care of all font displays on the screen

	// used as temporary constructs to hold transform data
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;

	//private functions, called in Renderer::Init()
	void SetupDevice(HWND hWnd);
	void SetupTextures();									// setup an object's texture, and returning it back to the object
	void SetupFont();

public:
	inline static Renderer* Instance()								// the instance of the singleton Renderer
	{
		static Renderer theRenderer;
		return &theRenderer;
	}
	void Init(HWND hWnd);											// initializes all systems of the class
	void Update();													// updates fps counter and sprite rotation
	void RenderOneFrame(eGameStates state, ObjectList lToDraw, Menu theMenu);// renders one frame onto the screen
	~Renderer();													// releases memory

	// get functions
	TexturePack	getTexturePack(int);
};