#pragma once

#include "Object.h"

class ObjectList
{
private:
	Object** List;
	void ForgiveCollisions(int elem);
	int maxSize;
	int currSize;

public:
	void Init(int size);
	void Update();
	void Push(Object* pObj);

	int getSize() { return currSize; }
	Object* operator[](int index);

};