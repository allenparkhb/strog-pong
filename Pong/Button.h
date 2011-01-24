#pragma once

#include "Object.h"

class Button: public Object
{
private:
	TexturePack m_tPack2;		// the texture for the button being pressed
	int top;					// the y position of the first button in the menu
	int spacing;				// the space between buttons
	eButton type;				// type of button (ie PLAY, OPTIONS)

public:
	TexturePack displayTexture;

	virtual void Init(int loc, ScreenDim dimensions) {}
	virtual void Init(int loc, ScreenDim dimensions, int texture1, int texture2);
	void ChangeTextures();
	virtual void Update(){int bob = 0;}
	virtual void MoveBack(){int bob = 0;}
	virtual void Bounce(int otherObject){int bob = 0;}
	virtual void setBack(){int bob = 0;}
};