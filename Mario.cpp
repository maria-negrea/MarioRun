#include "Mario.h"

Mario::Mario()
{
	length = 2;
	width = 2;
	height = 4.5;

	forwardSpeed = 0;
	acceleration = 0.05;
	maxSpeed = 1;
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
	
	forwardSpeed += acceleration;
	if(forwardSpeed > maxSpeed)
		forwardSpeed = maxSpeed;

	Translate(GetForward()*forwardSpeed);
}

void Mario::Jump()
{
	if(IsGrounded())
	{
		fallSpeed += 3;
	}
}

void Mario::Hit()
{
	forwardSpeed = -1;
}

void Mario::MoveRight()
{
	Translate(GetRight()*-1);
}

void Mario::MoveLeft()
{
	Translate(GetRight()*1);
}