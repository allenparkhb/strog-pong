#include "DirectInput.h"

// sets member variables to default values
DirectInput::DirectInput()
	: m_pDIObject(NULL)
	, m_pDIKeyboard(NULL)
	, m_pDIMouse(NULL)
{}

// initialize object and peripheral devices
void DirectInput::Init(HWND hWnd, HINSTANCE hInst)
{
	// create the direct input object
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDIObject, NULL);

	// use that object to create the keyboard and mouse devices
	m_pDIObject->CreateDevice(GUID_SysKeyboard, &m_pDIKeyboard, NULL);
	m_pDIObject->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL);

	// set data format
	m_pDIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	m_pDIMouse->SetDataFormat(&c_dfDIMouse);

	// set the cooperative level
	m_pDIKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	// acquire the devices
	HRESULT hr;

	hr = m_pDIKeyboard->Acquire();
	hr = m_pDIMouse->Acquire();
}

// handle input
void DirectInput::Update(int scrWidth, int scrHeight)
{
	HRESULT hr;

	// modify sprite[0] position based on arrow keys
	hr = m_pDIKeyboard->GetDeviceState(sizeof(m_kbBuffer), (void*)&m_kbBuffer);
	if(FAILED(hr))
		return;

	// modify sprite[0] based on arrow keys
	//if(m_kbBuffer[DIK_UP] & 0x80)			// check if 'UP' was pressed
	//	sprites[0]->vPos.y -= 5.0f;	
	//if(m_kbBuffer[DIK_LEFT] & 0x80)			// check if 'LEFT' was pressed
	//	sprites[0]->vPos.x -= 5.0f;
	//if(m_kbBuffer[DIK_DOWN] & 0x80)			// check if 'DOWN' was pressed
	//	sprites[0]->vPos.y += 5.0f;
	//if(m_kbBuffer[DIK_RIGHT] & 0x80)		// check if 'RIGHT' was pressed
	//	sprites[0]->vPos.x += 5.0f;

	//// modify sprite[5] based on WASD keys
	//if(m_kbBuffer[DIK_W] & 0x80)			// check if 'W' was pressed
	//	sprites[5]->vPos.y -= 5.0f;	
	//if(m_kbBuffer[DIK_A] & 0x80)			// check if 'A' was pressed
	//	sprites[5]->vPos.x -= 5.0f;
	//if(m_kbBuffer[DIK_S] & 0x80)			// check if 'S' was pressed
	//	sprites[5]->vPos.y += 5.0f;
	//if(m_kbBuffer[DIK_D] & 0x80)			// check if 'D' was pressed
	//	sprites[5]->vPos.x += 5.0f;

	////change the first sprite's rotation using the mouse
	//sprites[0]->fAngle += (m_mouseState.lX * 0.01f);

	////change the first sprite's scale using the mouse buttons
	//hr = m_pDIMouse->GetDeviceState(sizeof(m_mouseState), (void*)&m_mouseState);

	//if(FAILED(hr))
	//	return;

	//if(m_mouseState.rgbButtons[0] & 0x80)	// check if the left button was pressed
	//	sprites[0]->fScale *= 1.1f;
	//if(m_mouseState.rgbButtons[1] & 0x80)	// check if the right button was pressed
	//	sprites[0]->fScale *= 0.9f;
	//if(m_mouseState.rgbButtons[2] & 0x80)	// check if the middle button was pressed
	//	sprites[0]->fScale = 1.0f;

	//// check for position out of bounds
	//for(int i = 0; i < 6; i++)
	//{
	//	if(sprites[i]->vPos.x < 0 + sprites[i]->fBoundWid)
	//		sprites[i]->vPos.x = 0 + sprites[i]->fBoundWid;
	//	else if(sprites[i]->vPos.x > (scrWidth - sprites[i]->fBoundWid))
	//		sprites[i]->vPos.x = (scrWidth - sprites[i]->fBoundWid);

	//	if(sprites[i]->vPos.y < 0 + sprites[i]->fBoundLen)
	//		sprites[i]->vPos.y = 0 + sprites[i]->fBoundLen;
	//	else if(sprites[i]->vPos.y > scrHeight - sprites[i]->fBoundLen)
	//		sprites[i]->vPos.y = scrHeight - sprites[i]->fBoundLen;
	//}

	//// check for scale out of bounds
	//if(sprites[0]->fScale < 0.5)
	//	sprites[0]->fScale = 0.5f;
	//else if(sprites[0]->fScale > 3.0f)
	//	sprites[0]->fScale = 3.0f;

}

// release memory
DirectInput::~DirectInput()
{
	m_pDIKeyboard->Unacquire();
	m_pDIMouse->Unacquire();

	m_pDIObject->Release();
	m_pDIKeyboard->Release();
	m_pDIMouse->Release();
}