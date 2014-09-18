#pragma once
#include "Point3D.h"
#include "WorldObject.h"

class Collision
{
	Point3D direction;
	Point3D insidePositive;
	Point3D insideNegative;

	WorldObject* other;
public:
	Collision(Point3D insidePositive = 0,Point3D insideNegative = 0,WorldObject* other = NULL);
	~Collision();

	Point3D GetDirection();
	void SetDirection(Point3D direction);

	Point3D GetInsidePositive();
	Point3D GetInsideNegative();
	WorldObject* GetHitObject();

	bool IsCollision();
};

