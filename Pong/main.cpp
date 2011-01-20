#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <assert.h>
#include "resource.h"
#include "Renderer.h"
#include "DirectInput.h"
#include "Paddle.h"
#include "ObjectList.h"
#include "Usefuls.h"

/* Prototypes */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND OpenWindow(const char* cszClassName, const char* cszWindowName, int nCmdShow);

ObjectList CreateObjects(int size);
void Update(ObjectList vObjects);

ScreenDim g_Dimensions;

/*****************************************************\
* WinMain                                             *
\*****************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_Dimensions.width = 800;
	g_Dimensions.height = 600;

	/* Create the main window */
	HWND hWnd = OpenWindow("D3DWindow", "Gear Pong", nCmdShow);
	if (NULL == hWnd)
	{
		return E_FAIL;
	}

	RECT rClientRect;									// grab the screen dimensions
	GetClientRect(hWnd, &rClientRect);
	g_Dimensions.width = (float)(rClientRect.right - rClientRect.left);
	g_Dimensions.height = (float)(rClientRect.bottom - rClientRect.top);

	Renderer::Instance()->Init(hWnd);							// initialize renderer, giving it the window handler
	DirectInput::Instance()->Init(hWnd, hInstance);				// initialize DirectInput
	ObjectList lObjects;

	lObjects.Init(cnObjectNum);

	lObjects = CreateObjects(cnObjectNum);
	

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
		DirectInput::Instance()->PollDevices();				// get input
		Renderer::Instance()->RenderOneFrame(lObjects);		// draw one frame
		Update(lObjects);									// update

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
							g_Dimensions.width, g_Dimensions.height,
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
		case WM_KEYUP:
				switch(wParam)
				{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
				}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



ObjectList CreateObjects(int size)
{
	ObjectList objects;

	objects.Init(size);

	// create pointers to all the objects
	Wall* upperWall;
	Wall* lowerWall;
	Paddle* leftPaddle;
	Paddle* rightPaddle;
	//Ball*	PongBall;

	upperWall = new Wall;
	lowerWall = new Wall;
	leftPaddle = new Paddle;
	rightPaddle = new Paddle;
	//PongBall = new Ball;


	// using magic numbers for position placement until I can figure out texture resizing issue
	upperWall->Init(TOP, g_Dimensions);
	lowerWall->Init(BOTTOM, g_Dimensions);
	leftPaddle->Init(LEFT, DIK_A, DIK_Z, g_Dimensions);
	rightPaddle->Init(RIGHT, DIK_UP, DIK_DOWN, g_Dimensions);
	//PongBall->Init(g_iScreenWidth / 2, g_iScreenHeight / 2, g_Dimensions);

	//store all objects into a vector
	objects.Push(upperWall);
	objects.Push(lowerWall);
	objects.Push(leftPaddle);
	objects.Push(rightPaddle);
	//objects.Push(PongBall);

	return objects;
}

void Update(ObjectList vObjects)
{
	Renderer::Instance()->Update();
	vObjects.Update();
}