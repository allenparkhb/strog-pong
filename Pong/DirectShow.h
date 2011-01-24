#pragma once

#include <dshow.h>
#include "DirectInput.h"

class DirectShow
{
private:
	DirectShow();
	IGraphBuilder*		m_pGraphBuilder;
	IMediaControl*		m_pMediaControl;
	IMediaEvent*		m_pMediaEvent;
	IVideoWindow*		m_pVideoWindow;
	HWND				m_hWnd;
	bool isPlaying;
	bool isFinished;

public:
	inline static DirectShow* Ins()
	{
		static DirectShow instance;
		return &instance;
	}
	void Init(HWND hWnd);
	bool PlayVideo();			// returns true if the video is still playing
	void StopVideo();
	~DirectShow();

};