#pragma once
#include "Point3D.h"

enum View
{
	Up,
	Right,
	Forward
};

class Point2D
{
public:
	float x,y;

	Point2D(float x = 0, float y = 0);
	Point2D(Point3D viewUp ,View perspective );
	~Point2D();
};
