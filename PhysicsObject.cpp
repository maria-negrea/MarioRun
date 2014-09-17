#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{
	fallSpeed = 0;
}

PhysicsObject::~PhysicsObject()
{
}

bool PhysicsObject::IsGrounded()
{
	return translate.y == 0;
}

void PhysicsObject::Update()
{
	fallSpeed -= 0.3;
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