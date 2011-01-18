#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <assert.h>
#include "resource.h"
#include "Renderer.h"
#include "DirectInput.h"
#include "Paddle.h"
#include "Usefuls.h"

/* Prototypes */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND OpenWindow(const char* cszClassName, const char* cszWindowName, int nCmdShow);

ObjectList CreateObjects();
void Update(ObjectList vObjects);



/*****************************************************\
* WinMain                                             *
\*****************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	/* Create the main window */
	HWND hWnd = OpenWindow("D3DWindow", "Gear Pong", nCmdShow);
	if (NULL == hWnd)
	{
		return E_FAIL;
	}

	Renderer::Instance()->Init(hWnd);			// initialize renderer, giving it the window handler
	DirectInput::Instance()->Init(hWnd, hInstance);				// initialize DirectInput
	ObjectList vObjects;

	vObjects = CreateObjects();
	

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
		Renderer::Instance()->RenderOneFrame(vObjects);		// draw one frame
		Update(vObjects);									// update

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



ObjectList CreateObjects()
{
	ObjectList objects;

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


	upperWall->Init(300, 10);
	lowerWall->Init(300, cnScreenHeight - 60);
	leftPaddle->Init(300, 150, DIK_A, DIK_Z);
	rightPaddle->Init(1055, 150, DIK_UP, DIK_DOWN);
	//PongBall->Init(cnScreenWidth / 2, cnScreenHeight / 2);

	//store all objects into a vector
	objects.push_back(upperWall);
	objects.push_back(lowerWall);
	objects.push_back(leftPaddle);
	objects.push_back(rightPaddle);
	//objects.push_back(PongBall);

	return objects;
}

void Update(ObjectList vObjects)
{
	Renderer::Instance()->Update();

	for each(Object* pObject in vObjects)
	{
		pObject->Update();
	}
}