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
void DirectInput::PollDevices()
{
	HRESULT hr;

	// get the state of the keyboard
	hr = m_pDIKeyboard->GetDeviceState(sizeof(m_kbBuffer), (void*)&m_kbBuffer);
	if(FAILED(hr))
	{	
		ZeroMemory(m_kbBuffer, sizeof(m_kbBuffer));

		hr = m_pDIKeyboard->Acquire();
	}

	// get the state of the mouse
	hr = m_pDIMouse->GetDeviceState(sizeof(m_mouseState), (void*)&m_mouseState);

	if(FAILED(hr))
	{
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));

		hr = m_pDIMouse->Acquire();
	}

}

bool DirectInput::keyDown(char key)
{
	return (m_kbBuffer[key] & 0x80) != 0;
}

bool DirectInput::mouseButtonDown(int button)
{
	return (m_mouseState.rgbButtons[button] & 0x80) != 0;
}

float DirectInput::mouseDX()
{
	return (float)m_mouseState.lX;
}

float DirectInput::mouseDY()
{
	return (float)m_mouseState.lY;
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