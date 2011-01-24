#pragma once

#include "Object.h"
#include "Audio.h"

class ObjectList
{
private:
	Object** List;
	void ForgiveCollisions(int elem);
	int maxSize;
	int currSize;
	ScreenDim dimensions;

public:
	int p1Score;
	int p2Score;

	void Init(int size, ScreenDim dims);
	eScoreState Update();					// returns the win condition, if there is any
	void Push(Object* pObj);

	int getSize() { return currSize; }
	Object* operator[](int index);
	~ObjectList();

};