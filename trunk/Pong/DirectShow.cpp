#include "DirectShow.h"

DirectShow::DirectShow()
	: m_pGraphBuilder(NULL)
	, m_pMediaControl(NULL)
	, m_pMediaEvent(NULL)
	, m_pVideoWindow(NULL)
	, isPlaying(true)
	, isFinished(false)
{}

void DirectShow::Init(HWND hWnd)
{
	this->m_hWnd = hWnd;	// store a copy of hWnd in the class

	CoInitialize(NULL);	// initialize the COM library

	// create a filter graph manager to manage filters and data stream
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
							IID_IGraphBuilder, (void**)&m_pGraphBuilder);

	//media control is used to control streaming
	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);

	// media event receives events from the filter graph
	m_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&m_pMediaEvent);

	m_pGraphBuilder->RenderFile(L"Intro.avi", NULL);

	// video window
	m_pMediaControl->QueryInterface(IID_IVideoWindow, (void**)&m_pVideoWindow);

	// set up the window
	m_pVideoWindow->put_Owner((OAHWND)m_hWnd);
	m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE);	// set the style
	RECT WinRect;
	GetClientRect(m_hWnd, &WinRect);	// obtain the size of the window
	m_pVideoWindow->SetWindowPosition(WinRect.left, WinRect.top, // set the video size to the size of the window
										WinRect.right, WinRect.bottom);
	
}

bool DirectShow::PlayVideo()
{
	if(isPlaying)
	{
		m_pMediaControl->Run();

		long evCode;		// event code
		LONG_PTR eventParam1, eventParam2;
		m_pMediaEvent->GetEvent(&evCode, &eventParam1, &eventParam2, 0);

		if(evCode == EC_ERRORABORT || evCode == EC_COMPLETE ||		// if the video finishes or crashes
			DirectInput::Ins()->keyDown(DIK_RETURN))
		{
			isPlaying = false;
		}
	}
	else
	{
		if(!isFinished)
		{
			m_pMediaControl->Stop();
			m_pVideoWindow->put_Visible(OAFALSE);
			m_pVideoWindow->put_Owner((OAHWND)m_hWnd);
			isFinished = true;
		}
	}

	return !isFinished;
}

void DirectShow::StopVideo()
{
	m_pMediaControl->Stop();
}

DirectShow::~DirectShow()
{
	
	m_pMediaControl->Release();
	m_pMediaEvent->Release();
	m_pGraphBuilder->Release();			// needs to be after all other calls

	CoUninitialize();
}