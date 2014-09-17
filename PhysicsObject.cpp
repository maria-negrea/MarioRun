#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{
	fallSpeed = 0;
	isGrounded = true;
}

PhysicsObject::~PhysicsObject()
{
}

bool PhysicsObject::IsGrounded()
{
	return isGrounded || translate.y == 0;
}

void PhysicsObject::Update()
{
	fallSpeed -= 0.1;
	Translate(Point3D(0,fallSpeed,0));

	if(translate.y < 0)
	{
		translate.y = 0;
	}
	
	if(fallSpeed < 0)
	{
		if(IsGrounded())
		{
			fallSpeed = 0;
		}
	}
}
