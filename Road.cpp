#include "Road.h"
#include "Point2D.h"
#include "Segment2D.h"
#include<time.h>

Road::Road(void)
{
	srand(time(NULL));
	onRoadObject = NULL;

	GLfloat width = 20;
	GLfloat length = 40;
	Point3D lastRoad(0, 0, -length);
	Point3D currentRoad;
	roadSize=20;

	Point3D lastCurve = Point3D(0,0,1);

	double angle = 10;

	for(int i = 0; i < roadSize; i++)
	{
		Point3D newRoad = lastCurve.RotateY(angle);
		lastCurve = newRoad;

		if(i % 5 == 0)
			angle = rand() % 30 - 15;

		leftVector.push_back(newRoad.RotateY(-90)*width + lastRoad);
		rightVector.push_back(newRoad.RotateY(90)*width + lastRoad);

		roadVector.push_back(currentRoad);

		lastRoad = currentRoad;
		currentRoad += newRoad*length;
	}
}

Road::~Road(void)
{
}

void Road::DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	for(int i = 0; i < rightVector.size() - 1; i++)
	{
		glColor3f(1.0,1.0,1.0);
		if(i == roadIndex)
			glColor3f(1.0,0.0,0.0);

		glBegin(GL_QUADS);
			glVertex3f(leftVector[i].x, 0.1, leftVector[i].z);
			glVertex3f(rightVector[i].x, 0.1, rightVector[i].z);
			glVertex3f(rightVector[i + 1].x, 0.1, rightVector[i + 1].z);
			glVertex3f(leftVector[i + 1].x, 0.1, leftVector[i + 1].z);
		glEnd();
	}
}



#include<iostream>
using namespace std;

void Road::Update()
{
	if(onRoadObject != NULL)
	{
		if(!IsOnIndex())
		{
			roadIndex++;			
		}
		SetOnRoadAngle();
	
	}
}

void Road::SetOnRoadAngle()
{
	Point3D rotationDirection = (roadVector[roadIndex+1] - roadVector[roadIndex]);	
	Point3D relativObjPosition = (onRoadObject->GetTranslate()-roadVector[roadIndex]);

	double angle = (rotationDirection).AngleBetween(Point3D(0,0,1));

	if((rotationDirection).x < 0)
	{
		angle = -angle;
	}

	relativObjPosition = relativObjPosition.RotateY(angle);

	Point3D nextRotationDirection = (roadVector[roadIndex+2] - roadVector[roadIndex+1]);
	rotationDirection = rotationDirection + (nextRotationDirection-rotationDirection)*relativObjPosition.z/rotationDirection.Magnitude();

	angle = (rotationDirection).AngleBetween(Point3D(0,0,1));

	if((rotationDirection).x < 0)
	{
		angle = -angle;
	}

	onRoadObject->SetRotateY(angle);
}

bool Road::IsOnIndex()
{
	//cout<<roadIndex<<"X"<<endl;
	Point2D p1 = Point2D(rightVector[roadIndex],View::Up);
	Point2D p2 = Point2D(leftVector[roadIndex],View::Up);
	Point2D p3 = Point2D(leftVector[roadIndex+1],View::Up);
	Point2D p4 = Point2D(rightVector[roadIndex+1],View::Up);

	Point2D check = Point2D(onRoadObject->GetTranslate(),View::Up);

	Segment2D *polySegments = new Segment2D[4];
	polySegments[0] = Segment2D(p1,p2);
	polySegments[1] = Segment2D(p2,p3);
	polySegments[2] = Segment2D(p3,p4);
	polySegments[3] = Segment2D(p4,p1);

	Segment2D *lines = new Segment2D[4];
	lines[0] = Segment2D(check,p1);
	lines[1] = Segment2D(check,p2);
	lines[2] = Segment2D(check,p3);
	lines[3] = Segment2D(check,p4);

	//cout<<"POS "<<check.x<<" "<<check.y<<endl;
	//cout<<"p1X "<<p1.x<<" "<<p1.y<<endl;
	//cout<<"p2X "<<p2.x<<" "<<p2.y<<endl;
	//cout<<"p3X "<<p3.x<<" "<<p3.y<<endl;
	//cout<<"p4X "<<p4.x<<" "<<p4.y<<endl;

	if(lines[0].Intersects(polySegments[1]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}
	if(lines[0].Intersects(polySegments[2]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}
	if(lines[1].Intersects(polySegments[2]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}
	if(lines[1].Intersects(polySegments[3]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}
	if(lines[2].Intersects(polySegments[3]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}
	if(lines[2].Intersects(polySegments[0]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}
	if(lines[3].Intersects(polySegments[0]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}
	if(lines[3].Intersects(polySegments[1]))
	{
		//cout<<"FALSE"<<endl;
		return false;
	}

	//cout<<"TRUE"<<endl;
	return true;
}

Point3D Road::GetOnRoadPosition(Point3D point, GLfloat obstacleWidth)
{
	int indexZ=(int) point.z;	
	double posZ = point.z-indexZ;
	double posX = point.x;

	if(posX < 0)
	{
		posX = -posX;
	}
		
	Point3D intermediateZ = roadVector[indexZ] + (roadVector[indexZ+1] - roadVector[indexZ]) * posZ;

	int index=indexZ;

	Point3D intermediateX;
	if(point.x<0)
	{
		intermediateX = roadVector[indexZ] + (rightVector[index] - roadVector[indexZ]) * posX;
	}
	else
	{
		intermediateX = roadVector[indexZ] + (leftVector[index] - roadVector[indexZ]) * posX;
	}

	Point3D result = roadVector[indexZ] + (intermediateZ - roadVector[indexZ]) + (intermediateX - roadVector[indexZ]);

	if(result.x+obstacleWidth>leftVector[indexZ].x)
	{
		result.x-=obstacleWidth;
	}
	if(result.x-obstacleWidth>rightVector[indexZ].x)
	{
		result.x+=obstacleWidth;
	}
	return result;

}

void Road::SetRoadObject(WorldObject* object)
{
	onRoadObject = object;
	roadIndex = 1;
}

vector<Point3D> Road::GetRoad()
{
	return roadVector;
}

vector<Point3D> Road::GetLeft()
{
	return leftVector;
}

vector<Point3D> Road::GetRight()
{
	return rightVector;
}

int Road:: GetRoadSize()
{
	return roadSize;
}