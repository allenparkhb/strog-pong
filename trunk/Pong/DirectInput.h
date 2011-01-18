#ifndef DIRECTINPUT_H
#define DIRECTINPUT_H

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class DirectInput
{
private:
	DirectInput();								// as this is a singleton, the ctor is private

	IDirectInput8*			m_pDIObject;		// direct input device
	LPDIRECTINPUTDEVICE8	m_pDIKeyboard;		// device managing keyboard input
	LPDIRECTINPUTDEVICE8	m_pDIMouse;			// device managing mouse input
	char					m_kbBuffer[256];	// captures keyboard input
	DIMOUSESTATE			m_mouseState;		// captures mouse input

public:
	inline static DirectInput* Instance()		// the instance of the singleton DirectInput
	{
		static DirectInput input;
		return &input;
	}
	void Init(HWND hWnd, HINSTANCE hInst);
	void PollDevices();
	bool keyDown(char key);
	bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	~DirectInput();
};

#endif