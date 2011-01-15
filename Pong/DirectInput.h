#ifndef DIRECTINPUT_H
#define DIRECTINPUT_H

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class DirectInput
{
private:
	IDirectInput8*			m_pDIObject;		// direct input device
	LPDIRECTINPUTDEVICE8	m_pDIKeyboard;		// device managing keyboard input
	LPDIRECTINPUTDEVICE8	m_pDIMouse;			// device managing mouse input
	char					m_kbBuffer[256];	// captures keyboard input
	DIMOUSESTATE			m_mouseState;		// captures mouse input

public:
	DirectInput();
	inline static DirectInput* Instance()
	{
		static DirectInput theInput;
		return &theInput;
	}
	void Init(HWND hWnd, HINSTANCE hInst);
	void Update( int scrWidth, int scrHeight);
	~DirectInput();
};

#endif