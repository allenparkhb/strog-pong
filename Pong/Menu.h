#pragma once

#include "Button.h"

class Button;

class Menu
{
public:
	TexturePack m_mainBackground;
	TexturePack m_CreditsBackground;
	bool changedButtonTexture;		// used to determine if a button's texture has already been changed
	~Menu();

	Button* m_Buttons;
	eMenuStates eMState;		// flags if the menu is displaying the main menu or the credits
	eButton m_result;				// result of what button (if any) was pressed in the main menu
	int numButtons;
	void Init(ScreenDim dims);
	eButton Menu::Update(bool mousePressed, int mousePosX, int mousePosY);


};