#include "Collision.h"

Collision::Collision(Point3D direction,Point3D inside)
	:direction(direction),inside(inside)
{
}

Collision::~Collision()
{
}

Point3D Collision::GetDirection()
{
	return direction;
}

Point3D Collision::GetInside()
{
	return inside;
}