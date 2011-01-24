#pragma once

#include "Button.h"

class Menu
{
public:
	TexturePack m_mainBackground;
	TexturePack m_CreditsBackground;
	bool changedButtonTexture;		// used to determine if a button's texture has already been changed

	Button m_Buttons[4];

	bool isOnMain;					// flags if the menu is displaying the main menu or the credits
	int numButtons;
	void Init(ScreenDim dims);
	eButton Menu::Update(bool mousePressed, int mousePosX, int mousePosY);
};