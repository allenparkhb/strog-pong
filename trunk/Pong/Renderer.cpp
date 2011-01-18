#include "Renderer.h"


// used to make debug easier when dealing with DirectX
#ifdef _DEBUG
#ifndef HR

#define HR(x)					\
	{								\
	HRESULT hr = x;				\
	if (FAILED(hr))				\
		{							\
		DXTRACE_ERR(#x, hr);	\
		DebugBreak();			\
		}							\
	}
#endif
#else
#ifndef HR
#define HR(x) x;
#endif
#endif

// initializes most member variables to default values
Renderer::Renderer()
: m_pD3DDevice(NULL)
, m_pD3DSprite(NULL)
, m_hWnd(NULL)
, m_bWindowed(true)
, m_fScreenHeight(0)
, m_fScreenWidth(0)
{
}

void Renderer::Init(HWND hWnd)
{
	SetupDevice(hWnd);
	SetupTextures();
	SetupFont();
}

void Renderer::SetupDevice(HWND hWnd)
{
	IDirect3D9* pD3DObject = NULL;
	pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);		// create the d3dobject

	m_hWnd = hWnd;										// make a copy of hWnd that Renderer can use

	RECT rClientRect;									// grab the screen dimensions
	if(!::GetClientRect(m_hWnd, &rClientRect))
	{
		throw "GetClientRect() failed";
	}
	m_fScreenWidth = (float)(rClientRect.right - rClientRect.left);
	m_fScreenHeight = (float)(rClientRect.bottom - rClientRect.top);

	D3DCAPS9 D3DCaps;
	HR(pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &D3DCaps));


	// determine what type of vertex processing to use
	DWORD dwBehaviorFlags = 0;

	if(D3DCaps.VertexProcessingCaps != 0)
	{
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}	

	//set up present parameters
	m_D3Dpp.hDeviceWindow			= m_hWnd;
	m_D3Dpp.Windowed				= m_bWindowed;
	m_D3Dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	m_D3Dpp.EnableAutoDepthStencil	= TRUE;
	m_D3Dpp.BackBufferCount			= 1;
	m_D3Dpp.BackBufferFormat		= D3DFMT_X8R8G8B8;
	m_D3Dpp.BackBufferWidth			= (int)m_fScreenWidth;
	m_D3Dpp.BackBufferHeight		= (int)m_fScreenHeight;
	m_D3Dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	m_D3Dpp.Flags					= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	m_D3Dpp.MultiSampleQuality		= 0;
	m_D3Dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;

	// setup the d3ddevice using the d3dobject and present parameters
	pD3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwBehaviorFlags, &m_D3Dpp, &m_pD3DDevice);

	pD3DObject->Release();
}

void Renderer::SetupFont()
{
	ID3DXFont* tempFont = NULL;

	// set up font used to display fps counter
	D3DXCreateFont(m_pD3DDevice, Font.getFontSize(), 0, FW_BOLD, 0, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman"), &tempFont);

	Font.Init(tempFont);
}

void Renderer::SetupTextures()
{

	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);	// set up sprite handler

	// set up the textures to be used
	D3DXCreateTextureFromFileEx(m_pD3DDevice, "wall.png", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255),
		&m_tpWall.imgInfo, 0, &m_tpWall.lpTexture);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, "paddle.png", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255),
		&m_tpPaddle.imgInfo, 0, &m_tpPaddle.lpTexture);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, "ball.png", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255),
		&m_tpBall.imgInfo, 0, &m_tpBall.lpTexture);
}

void Renderer::Update()
{
	Font.Update();
}

void Renderer::RenderOneFrame(ObjectList vToDraw)
{
	if(NULL == m_pD3DDevice) return;

	//check for lost device
	HRESULT hDevState = m_pD3DDevice->TestCooperativeLevel();
	switch(hDevState)
	{
	case D3DERR_DEVICELOST:
		// if device is lost, stop and check it next frame
		::OutputDebugString("Device Lost");
		::Sleep(1000);
		return;
	case D3DERR_DEVICENOTRESET:
		// device still not found after a while, reset the D3D device
		if(FAILED(m_pD3DDevice->Reset(&m_D3Dpp)))
		{
			::OutputDebugString("Reset failed");
			return;
		}
		break;
	}

	// clear back buffer and z-buffer
	HR(m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));


	HRESULT hr = m_pD3DDevice->BeginScene();		// begin preparing the frame
	if(FAILED(hr))
	{
		return;										// if preparation failed, stop rendering
	}

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);		// prepare to draw sprites to the screen

	for each(Object* pObject in vToDraw)
	{
		D3DXMatrixTranslation(&matTrans, 
			pObject->getPosition().x, 
			pObject->getPosition().y, 
			0);
		D3DXMatrixRotationZ(&matRotation, pObject->getAngle());
		D3DXMatrixScaling(&matScale, pObject->getScale(), pObject->getScale(), 0);


		D3DXMatrixMultiply(&matWorld, &matScale, &matRotation);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matTrans);

		m_pD3DSprite->SetTransform(&matWorld);
		m_pD3DSprite->Draw(pObject->getTexture(), 0, &pObject->getCenter(),
			0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_pD3DSprite->End();							// stop drawing sprites

	Font.Draw();

	hr = m_pD3DDevice->EndScene();					// stop preparing the frame

	if(FAILED(hr)) 
	{
		return;										// stop rendering if EndScene failed
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);  //display back buffer onto the screen
}

// release memory
Renderer::~Renderer()
{
	m_pD3DDevice->Release();
	m_pD3DSprite->Release();
	m_tpWall.lpTexture->Release();
	m_tpPaddle.lpTexture->Release();
	m_tpBall.lpTexture->Release();
}

TexturePack Renderer::getTexturePack(int type)
{
	if(type == WALL)
		return m_tpWall;
	else if(type == PADDLE)
		return m_tpPaddle;
	else if(type == BALL)
		return m_tpBall;

	else
		return m_tpBall;
}