#include "Point2D.h"

Point2D::~Point2D(void)
{
}

Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point2D::Point2D(Point3D point,View perspective)
{
	switch(perspective)
	{
		case View::Up:
			x = point.x;
			y = point.z;
			break;
		case View::Right:
			x = point.z;
			y = point.y;			
			break;
		case View::Forward:
			x = point.x;
			y = point.y;
			break;
	}
}
