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

#include<iostream>

bool Segment2D::IsOnSegment(Point2D point)
{

	double minX, maxX, minY, maxY;

	if(p1.x > p2.x)
	{
		maxX = p1.x;
		minX = p2.x;
	}
	else
	{
		maxX = p2.x; 
		minX = p1.x;
	}


	if(p1.y > p2.y)
	{
		maxY = p1.y;
		minY = p2.y;
	}
	else
	{
		maxY = p2.y; 
		minY = p1.y;
	}

	//std::cout<<"INT "<<point.x<<" "<<point.y<<std::endl;
	//std::cout<<"INT "<<minX<<" "<<maxX<<std::endl;
	//std::cout<<"INT "<<minY<<" "<<maxY<<std::endl<<std::endl;

	return point.x > minX && point.x < maxX && point.y > minY && point.y < maxY;
}