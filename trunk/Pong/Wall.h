#ifndef WALL_H
#define WALL_H

#include "Object.h"

class Wall: public Object
{
public:
	virtual void Init(int xPos, int yPos);
	virtual void Update(){}
	
};

#endif