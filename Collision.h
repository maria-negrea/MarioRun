#pragma once
#include "Point3D.h"

class Collision
{
	Point3D direction;
	Point3D inside;
public:
	Collision(Point3D direction, Point3D inside);
	~Collision();

	Point3D GetDirection();
	Point3D GetInside();
};
