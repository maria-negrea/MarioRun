#include "Mario.h"

Mario::Mario()
{
}

Mario::~Mario()
{

}

void Mario::DrawObject()
{

}

void Mario::Update()
{
	PhysicsObject::Update();
	Translate(GetForward()*5);
}

void Mario::Jump()
{
	if(IsGrounded())
	{
		fallSpeed += 3;
	}
}


void Mario::MoveRight()
{
	Translate(GetRight()*-1);
}

void Mario::MoveLeft()
{
	Translate(GetRight()*1);
}