#pragma once
#include "Wall.h"
#include "DirectInput.h"


class Paddle: public Wall
{
private:
	unsigned char m_upKey;
	unsigned char m_downKey;
	int m_speed;

public:
	int score;
	virtual void Init(int loc, ScreenDim dimensions) {}
	virtual void Init(int loc, char up, char down, ScreenDim dimensions);
	virtual void Update();
	virtual void MoveBack();

};