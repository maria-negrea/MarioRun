#include "Mario.h"

Mario::Mario()
{
	length = 2.0;
	width = 2.0;
	height = 9.5;
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
	Translate(GetForward()*0.5);
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