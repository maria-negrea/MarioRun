#pragma once
#include "Point2D.h"

class Line
{
	float m;
	float b;
public:
	Line(Point2D p1, Point2D p2);
	~Line();

	Point2D Intersection(Line other);
};
