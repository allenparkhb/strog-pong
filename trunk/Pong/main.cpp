#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsX.h>
#include <assert.h>
#include "resource.h"
#include "Renderer.h"
#include "Audio.h"
#include "DirectInput.h"
#include "DirectShow.h"
#include "Paddle.h"
#include "Ball.h"
#include "ObjectList.h"

/* Prototypes */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR psCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OpenWindow(const char* cszClassName, const char* cszWindowName, int nCmdShow);

ObjectList CreateObjects(int size);
eScoreState UpdateGame();
bool Initialize(HINSTANCE hInstance, int nCmdShow);
void Update(HINSTANCE, int nCmdShow);

eGameStates eState = LOADING;		// the state of the game
ScreenDim g_Dimensions;				// dimensions of the screen
HWND hWnd;							// main window handler
ObjectList lObjects;				// list of game objects
Menu g_GameMenu;					// menu


bool isRunning = true;

// used for mouse click detection
int g_mousePosX;
int g_mousePosY;
bool g_mouseDown = false;

/*****************************************************\
* WinMain                                             *
\*****************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	/* Message loop */
	MSG uMsg;
    memset(&uMsg, 0, sizeof(uMsg));
	while (uMsg.message != WM_QUIT && isRunning)
	{
		/* Handle incoming messages */
		while (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}
		Update(hInstance, nCmdShow);				// update the program (acts as a FSM)
	}

    UnregisterClass("D3DWindow", hInstance);

	return uMsg.wParam;
}

void OpenWindow(const char* cszWinClassName, const char* cszWindowName, int nCmdShow)
{
	/* Register window class and create window */

	WNDCLASSEX winClass;

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
		return;
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
				case VK_ESCAPE:					// pressing escape brings the game back to the menu
					eState = MENU;
					break;
				}
		case WM_LBUTTONDOWN:					// if the mouse was clicked, grab the position
			g_mousePosX = GET_X_LPARAM(lParam);
			g_mousePosY = GET_Y_LPARAM(lParam);
			g_mouseDown = true;					// set the mouse down flag to true
			break;
		case WM_LBUTTONUP:
			g_mouseDown = false;
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

ObjectList CreateObjects(int size)
{
	ObjectList objects;

	objects.Init(size, g_Dimensions);

	// create pointers to all the objects
	Wall* upperWall;
	Wall* lowerWall;
	Paddle* leftPaddle;
	Paddle* rightPaddle;
	Ball*	PongBall;

	upperWall = new Wall;
	lowerWall = new Wall;
	leftPaddle = new Paddle;
	rightPaddle = new Paddle;
	PongBall = new Ball;

	upperWall->Init(TOP, g_Dimensions);
	lowerWall->Init(BOTTOM, g_Dimensions);
	leftPaddle->Init(LEFT, DIK_A, DIK_Z, g_Dimensions);
	rightPaddle->Init(RIGHT, DIK_UP, DIK_DOWN, g_Dimensions);
	PongBall->Init(MIDDLE, g_Dimensions);

	//store all objects into a vector
	objects.Push(upperWall);
	objects.Push(lowerWall);
	objects.Push(leftPaddle);
	objects.Push(rightPaddle);
	objects.Push(PongBall);

	return objects;
}

eScoreState UpdateGame()
{
	Renderer::Instance()->Update();
	return lObjects.Update();
}

bool Initialize(HINSTANCE hInstance, int nCmdShow)
{
	g_Dimensions.width = 800;
	g_Dimensions.height = 600;

	/* Create the main window */
	OpenWindow("D3DWindow", "Pong", nCmdShow);
	if (NULL == hWnd)
	{
		return false;
	}

	RECT rClientRect;									// grab the screen dimensions
	GetClientRect(hWnd, &rClientRect);
	g_Dimensions.width = (int)(rClientRect.right - rClientRect.left);
	g_Dimensions.height = (int)(rClientRect.bottom - rClientRect.top);

	Renderer::Instance()->Init(hWnd);					// initialize renderer, giving it the window handler
	DirectInput::Ins()->Init(hWnd, hInstance);			// initialize DirectInput
	DirectShow::Ins()->Init(hWnd);
	Audio::Ins()->Init();								// initialize the Sound Engine
	g_GameMenu.Init(g_Dimensions);
	

	lObjects.Init(cnObjectNum, g_Dimensions);			// prepares the object list to store objects

	lObjects = CreateObjects(cnObjectNum);				// create the objects and store them in the list

	return true;
}

void Update(HINSTANCE hInstance, int nCmdShow)
{
	eButton menuResult = NUMBUTTONS;	// used to determine what button was pressed in the menu
	switch(eState)
	{
	case LOADING:						// initialize all aspects of the game
		if(Initialize(hInstance, nCmdShow))
			eState = INTRO;				// then directly after, switch to intro video
		else
			eState = QUIT;
		break;
	case INTRO:							// play the video until it's supposed to stop
		if(!DirectShow::Ins()->PlayVideo())
		{
			eState = MENU;
		}
		break;
	case MENU:
		menuResult = g_GameMenu.Update(g_mouseDown, g_mousePosX, g_mousePosY);
		Renderer::Instance()->RenderOneFrame(MENU, lObjects, g_GameMenu);
		Audio::Ins()->StreamOff();

		// change states if a button was pressed
		switch(menuResult)
		{
		case PLAYBUTTON:
			eState = GAME;				// set the state to play the game
			Audio::Ins()->StreamOn();	// turn on background music
			Renderer::Instance()->RenderOneFrame(GAME, lObjects, g_GameMenu);	// render one frame
			Sleep(500);					// sleep so that DirectInput doesn't confuse the button being
			break;						// clicked with the click to start the game
		case OPTIONSBUTTON:
			break;						// TODO: Create an options menu
		case CREDITSBUTTON:				// set state to credits to display the credits
			eState = CREDITS;
			break;
		case QUITBUTTON:				// set state to quit the game
			eState = QUIT;
		}
		break;
	case GAME:
		eScoreState score;										// used to check if the game has been won
		Renderer::Instance()->RenderOneFrame(GAME, lObjects, g_GameMenu);			// draw one frame
		score = UpdateGame();									// update
		if(score != INPROGRESS)			// if the game is over
		{
			lObjects.NewGame();			// start a new game
			eState = MENU;				// go back to the menu
		}
		break;
	case CREDITS:	// update the menu and render it (the credits page is a part of the menu)
		menuResult = g_GameMenu.Update(g_mouseDown, g_mousePosX, g_mousePosY);
		Renderer::Instance()->RenderOneFrame(MENU, lObjects, g_GameMenu);
		if(menuResult == BACK)	// if the user clicks, go back to the main menu
			eState = MENU;
		break;
	case QUIT:					// if the user quits, flag the game to quit and shut off the sound
		Audio::Ins()->StreamOff();
		isRunning = false;
		break;
	}
	DirectInput::Ins()->PollDevices();	// get input
	Audio::Ins()->Update();				// give the sound engine time to work
}