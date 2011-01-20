#include "ObjectList.h"

void ObjectList::Init(int size)
{
	maxSize = size;
	List = new Object*[maxSize];
	currSize = 0;
}

void ObjectList::ForgiveCollisions(int elem)
{
	bool collided = true;

	for(int i = 0; i < currSize; i++)
	{
		if(i != elem)
		{
			/*if(abs(List[i]->getPosition().x - List[elem]->getPosition().x) < 
				List[i]->getImgInfo().Width + List[elem]->getImgInfo().Width
				&&
				abs(List[i]->getPosition().y - List[elem]->getPosition().y) <
				List[i]->getImgInfo().Height + List[elem]->getImgInfo().Height)
			{
				collided = true;
			}
			else
				collided = false;*/

			if(!(List[i]->m_BoundingRect.bottom < List[elem]->m_BoundingRect.top ||
			   List[i]->m_BoundingRect.top > List[elem]->m_BoundingRect.bottom ||
			   List[i]->m_BoundingRect.right < List[elem]->m_BoundingRect.left ||
			   List[i]->m_BoundingRect.left > List[elem]->m_BoundingRect.right))
			{
				collided = true;
			}
			else
				collided = false;

			if(collided)
			{
				List[elem]->MoveBack();
			}

		}
	}
}

void ObjectList::Update()
{
	for(int i = 0; i < currSize; i++)
	{
		List[i]->Update();
		ForgiveCollisions(i);
	}
}

void ObjectList::Push(Object* pObj)
{
	if(currSize < maxSize)
	{
		List[currSize] = pObj;
		currSize++;
	}
}

Object* ObjectList::operator [](int index)
{
	return List[index];
}
