#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(double bounce)
	:bounce(bounce)
{
	fallSpeed = 0;
	isGrounded = true;
}

PhysicsObject::~PhysicsObject()
{
}

bool PhysicsObject::IsGrounded()
{
	return isGrounded && translate.y == 0;
}

void PhysicsObject::Update()
{
	fallSpeed -= 0.1;
	GLfloat lastY = translate.y;

	Translate(Point3D(0,fallSpeed,0));

	if(translate.y < 0)
		translate.y = 0;

	if(abs(lastY-translate.y) < 0.00000001)
	{
		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}
	
	if(fallSpeed < 0)
	{
		if(IsGrounded())
		{
			if(bounce > 0.01)
			{
				int q = 1;
			}
			fallSpeed = -fallSpeed*bounce;
			if(abs(fallSpeed) < 0.0001)
				fallSpeed = 0;
		}
	}
}
