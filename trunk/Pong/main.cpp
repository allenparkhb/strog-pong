#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <assert.h>
#include "resource.h"
#include "Renderer.h"
#include "DirectInput.h"

const unsigned int cnScreenWidth = 800;
const unsigned int cnScreenHeight = 600;

/* Prototypes */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND OpenWindow(const char* cszClassName, const char* cszWindowName, int nCmdShow);

/*****************************************************\
* WinMain                                             *
\*****************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	/* Create the main window */
	HWND hWnd = OpenWindow("D3DWindow", "Pong Clone", nCmdShow);
	if (NULL == hWnd)
	{
		return E_FAIL;
	}

	Renderer::Instance()->Init(hWnd);				// initialize renderer, giving it the window handler
	DirectInput::Instance()->Init(hWnd, hInstance);	// initialize DirectInput

	/* Message loop */
	MSG uMsg;
    memset(&uMsg, 0, sizeof(uMsg));
	while (uMsg.message != WM_QUIT)
	{
		/* Handle incoming messages */
		while (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}


	}

    UnregisterClass("D3DWindow", hInstance);

	return uMsg.wParam;
}


HWND OpenWindow(const char* cszWinClassName, const char* cszWindowName, int nCmdShow)
{
	/* Register window class and create window */

	WNDCLASSEX winClass;
	HWND hWnd;

	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	assert(NULL != hInstance);
	HICON hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	assert(NULL != hIcon);

	winClass.lpszClassName = cszWinClassName;
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hIcon	       = hIcon;
    winClass.hIconSm	   = hIcon;
	winClass.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if (0 == RegisterClassEx(&winClass))
	{
		return NULL;
	}

	hWnd = ::CreateWindowEx(NULL,
							cszWinClassName,
							cszWindowName,
							WS_OVERLAPPEDWINDOW,
							0, 0,
							cnScreenWidth, cnScreenHeight,
							NULL, NULL, ::GetModuleHandle(NULL), NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CLOSE:
				PostQuitMessage(0);
				break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

