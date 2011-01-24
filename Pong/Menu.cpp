#include "Menu.h"

void Menu::Init(ScreenDim dims)
{
	m_Buttons = new Button[4];

	m_mainBackground = Renderer::Instance()->getTexturePack(MAINMENU);
	m_CreditsBackground = Renderer::Instance()->getTexturePack(CREDITSPAGE);
	eMState = MAINSTATE;
	numButtons = NUMBUTTONS;
	eButton m_result = NUMBUTTONS;

	m_Buttons[0].Init(PLAYBUTTON, dims, PLAY_UNP, PLAY_P);
	m_Buttons[1].Init(OPTIONSBUTTON, dims, OPTIONS_UNP, OPTIONS_P);
	m_Buttons[2].Init(CREDITSBUTTON, dims, CREDITS_UNP, CREDITS_P);
	m_Buttons[3].Init(QUITBUTTON, dims, QUIT_UNP, QUIT_P);
}

eButton Menu::Update(bool mousePressed, int mousePosX, int mousePosY)
{
	m_result = NUMBUTTONS;
	// update procedure in the main menu
	switch(eMState)
	{
	case MAINSTATE:	// if the user is on the main menu
		// check if any buttons are pressed if on the main screen
		

		if(mousePressed)
		{
			for(int i = 0; i < numButtons; i++)
			{

					if(m_Buttons[i].m_BoundingRect.top < mousePosY &&
					m_Buttons[i].m_BoundingRect.bottom > mousePosY &&
					m_Buttons[i].m_BoundingRect.left < mousePosX &&
					m_Buttons[i].m_BoundingRect.right > mousePosX)
					{
						m_Buttons[i].ChangeTextures();
						m_result = (eButton)i;
						Audio::Ins()->PlayClickSound();
					}
			}
		}

		if(m_result == CREDITSBUTTON)
			eMState = CREDITSSTATE;

		// return the value of what button was pressed, or NONE if none were pressed
		return m_result;

	case CREDITSSTATE:
		// if the user clicks, simply return to the main page
		if(mousePressed)
		{
			eMState = MAINSTATE;
		}
		return BACK;
	}
}

Menu::~Menu()
{
	//delete [] m_Buttons;
}