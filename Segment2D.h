#pragma once
#include "Point2D.h"
#include "Line.h"


class Segment2D
{
	Point2D p1,p2;
public:
	Segment2D(Point2D p1 = Point2D(),Point2D p2 = Point2D());
	~Segment2D();

	Line GetLine();
	bool Intersects(Segment2D other);
	
	bool IsOnSegment(Point2D point);
};
