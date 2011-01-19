#pragma once
#include "Wall.h"
#include "DirectInput.h"


class Paddle: public Wall
{
private:
	int m_upperLimit;
	int m_lowerLimit;
	unsigned char m_upKey;
	unsigned char m_downKey;
	int m_speed;

public:
	virtual void Init(int xPos, int yPos, char up, char down);
	virtual void Update();

};