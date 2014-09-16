#include "Mario.h"

Mario::Mario()
	:Mesh(MarioPoints(),MarioTriangles(),4,1)
{
}

Mario::~Mario()
{

}


Point3D* Mario::MarioPoints()
{
	Point3D *marioPoints = new Point3D[10];

	marioPoints[0] = Point3D(0,1,1);
	marioPoints[1] = Point3D(1,1,0.4);
	marioPoints[2] = Point3D(1,1,-0.4);
	marioPoints[3] = Point3D(0.4,1,-1);

	return marioPoints;
}

Triangle* Mario::MarioTriangles()
{
	Triangle* triangles;
	return triangles;	
}