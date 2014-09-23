#include "Collision.h"

Collision::Collision(Point3D insidePositive,Point3D insideNegative,WorldObject* other)
	:insidePositive(insidePositive*1.001),insideNegative(insideNegative*1.001),other(other)
{
}

Collision::~Collision()
{
}

Point3D Collision::GetDirection()
{
	return direction;
}

void Collision::SetDirection(Point3D direction)
{
	this->direction = direction;
}

Point3D Collision::GetInsidePositive()
{
	return insidePositive;
}

Point3D Collision::GetInsideNegative()
{
	return insideNegative;
}

bool Collision::IsCollision()
{
	return other != NULL;
}

WorldObject* Collision::GetHitObject()
{
	return other;
}
