#include "Mario.h"

Mario::Mario()
	:Mesh(MarioPoints(),MarioTriangles(),16,16)
{
}

Mario::~Mario()
{

}


Point3D* Mario::MarioPoints()
{
	Point3D *marioPoints = new Point3D[16];

	marioPoints[0] = Point3D(-0.4,1,1);
	marioPoints[1] = Point3D(0.4,1,1);
	
	marioPoints[2] = Point3D(1,1,0.4);
	marioPoints[3] = Point3D(1,1,-0.4);
	
	marioPoints[4] = Point3D(0.4,1,-1);
	marioPoints[5] = Point3D(-0.4,1,-1);

	marioPoints[6] = Point3D(-1,1,-0.4);
	marioPoints[7] = Point3D(-1,1,0.4);


	marioPoints[8] = Point3D(-0.4,-1,0.9);
	marioPoints[9] = Point3D(0.4,-1,0.9);

	marioPoints[10] = Point3D(0.9,-0.8,0.4);
	marioPoints[11] = Point3D(0.9,-0.4,-0.4);
	
	marioPoints[12] = Point3D(0.4,-0.4,-0.9);
	marioPoints[13] = Point3D(-0.4,-0.4,-0.9);

	marioPoints[14] = Point3D(-0.9,-0.4,-0.4);
	marioPoints[15] = Point3D(-0.9,-0.8,0.4);

	return marioPoints;
}

Triangle* Mario::MarioTriangles()
{
	Triangle* triangles = new Triangle[16];

	for(int i=0;i<7;i++)
	{
		triangles[i*2] = Triangle(i,i+7,i+8);
		triangles[i*2+1] = Triangle(i,i+1,i+8);
	}
	triangles[14] = Triangle(6,7,13);
	triangles[15] = Triangle(6,0,7);
	return triangles;	
}