#include "Object.h"
#include "DirectInput.h"

class Ball: public Object
{
private:
	D3DXVECTOR3 m_vOldPosition;
	D3DXVECTOR3 m_vDirection;	// direction of the ball's movement
	int m_speed;				// scalar speed of the ball
	D3DXVECTOR3 m_vVelocity;	// velocity = direction * speed
	D3DXVECTOR3 m_vStartPos;

public:
	virtual void Init(int loc, ScreenDim dimensions);
	virtual void Update();
	virtual void MoveBack();
	void Bounce(int type);
	void setBack();
};