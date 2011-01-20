#pragma once

#include "Object.h"

class Wall: public Object
{
public:
	virtual void Init(int loc, ScreenDim dimensions);
	virtual void Update(){}
	virtual void MoveBack(){}
	
};

