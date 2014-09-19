#include "Line.h"

Line::Line(Point2D p1, Point2D p2)
{
	m = (p1.y-p2.y)/(p1.x-p2.x);
	b = p1.y-m*p1.x;
}

Line::~Line(void)
{
}

Point2D Line::Intersection (Line other)
{
	float x = (other.b-b)/(m-other.m);
	float y = m*x+b;

	return Point2D(x,y);
}
