#include "Menu.h"

void Menu::Init(ScreenDim dims)
{
	m_mainBackground = Renderer::Instance()->getTexturePack(MAINMENU);
	m_CreditsBackground = Renderer::Instance()->getTexturePack(CREDITSPAGE);
	isOnMain = true;
	numButtons = MAXBUTTONS;


	m_Buttons[0].Init(PLAYBUTTON, dims, PLAY_UNP, PLAY_P);
	m_Buttons[1].Init(OPTIONSBUTTON, dims, OPTIONS_UNP, OPTIONS_P);
	m_Buttons[2].Init(CREDITSBUTTON, dims, CREDITS_UNP, CREDITS_P);
	m_Buttons[3].Init(QUITBUTTON, dims, QUIT_UNP, QUIT_P);
}

eButton Menu::Update(bool mousePressed, int mousePosX, int mousePosY)
{
	if(isOnMain)	// if the user is on the main menu
	{
		// check if any buttons are pressed 
		eButton result = NONE;

		if(mousePressed)
		{
			for(int i = PLAYBUTTON; i < numButtons; i++)
			{

					if(m_Buttons[i].m_BoundingRect.top < mousePosY &&
					m_Buttons[i].m_BoundingRect.bottom > mousePosY &&
					m_Buttons[i].m_BoundingRect.left < mousePosX &&
					m_Buttons[i].m_BoundingRect.right > mousePosX)
					{
						m_Buttons[i].ChangeTextures();
						result = (eButton)i;
					}
			}
	}

		// return the value of what button was pressed, or NONE if none were pressed
		return result;
	}
}