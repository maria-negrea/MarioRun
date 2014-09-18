#include "Segment2D.h"

Segment2D::Segment2D(Point2D p1, Point2D p2)
	:p1(p1),p2(p2)
{
}

Segment2D::~Segment2D()
{
}

bool Segment2D::Intersects(Segment2D other)
{
	Point2D intersectionPoint = GetLine().Intersection(other.GetLine());

	if(IsOnSegment(intersectionPoint) && other.IsOnSegment(intersectionPoint))
	{
		return true;
	}
	return false;
}

Line Segment2D::GetLine()
{
	return Line(p1,p2);
}

bool Segment2D::IsOnSegment(Point2D point)
{
	float minX, maxX, minY, maxY;

	(p1.x > p2.x)?maxX = p1.x,minX = p2.x:maxX = p2.x, minX = p1.x;
	(p1.y > p2.y)?maxY = p1.y,minY = p2.y:maxY = p2.y, minY = p1.y;

	return point.x > minX && point.x < maxX && point.y > minY && point.y < maxY;
}