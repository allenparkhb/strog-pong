#include "ObjectList.h"

void ObjectList::Init(int size, ScreenDim dims)
{
	p1Score = p2Score = 0;
	this->dimensions = dims;
	maxSize = size;
	List = new Object*[maxSize];
	currSize = 0;
}

void ObjectList::ForgiveCollisions(int elem)
{
	bool collided;

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
				List[elem]->MoveBack();					// move back if collided
				if(List[elem]->eType == BALL)
				{
					List[elem]->Bounce(List[i]->eType);	// ball bounces off object
				}
			}

			// check if ball went out of bounds and assign points
			if(List[elem]->eType == BALL)
			{
				if(List[elem]->m_BoundingRect.left <= 0)
				{
					p2Score++;
					List[elem]->setBack();
				}
				else if(List[elem]->m_BoundingRect.right >= dimensions.width)
				{
					p1Score++; 
					List[elem]->setBack();
				}
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
