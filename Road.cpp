#include "Road.h"
#include "Point2D.h"
#include "Segment2D.h"
#include<time.h>

Road::Road(void)
{
	srand(time(NULL));

	GLfloat width = 20;
	GLfloat length = 40;
	Point3D lastRoad(0, 0, -length);
	Point3D currentRoad;

	Point3D lastCurve = Point3D(0,0,1);

	double angle = 10;

	for(int i = 0; i < 40; i++)
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
		for(unsigned j = 0; j<onRoadObjects.size();j++)
		{
			if(i == onRoadObjects[j].GetIndex())
				glColor3f(1.0,0.0,0.0);
		}

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
	for(unsigned i = 0; i<onRoadObjects.size();i++)
	{
		while(!IsOnIndex(onRoadObjects[i]))
		{
			onRoadObjects[i].IncrementIndex();
		}
		SetOnRoadAngle(onRoadObjects[i]);
	}
}

void Road::SetOnRoadAngle(RoadWorldObjectLink link)
{
	int roadIndex = link.GetIndex();
	WorldObject* onRoadObject = link.GetObject();

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

bool Road::IsOnIndex(RoadWorldObjectLink link)
{
	int roadIndex = link.GetIndex();
	WorldObject* onRoadObject = link.GetObject();

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

	if(lines[0].Intersects(polySegments[1]))
	{
		return false;
	}
	if(lines[0].Intersects(polySegments[2]))
	{
		return false;
	}
	if(lines[1].Intersects(polySegments[2]))
	{
		return false;
	}
	if(lines[1].Intersects(polySegments[3]))
	{
		return false;
	}
	if(lines[2].Intersects(polySegments[3]))
	{
		return false;
	}
	if(lines[2].Intersects(polySegments[0]))
	{
		return false;
	}
	if(lines[3].Intersects(polySegments[0]))
	{
		return false;
	}
	if(lines[3].Intersects(polySegments[1]))
	{
		return false;
	}

	return true;
}

Point3D Road::GetCoinPoint(double index, double gradient, int side)
{
	double pos = index - (int)index;

	if(side == 0)
	{
		Point3D result = roadVector[(int)index] + (roadVector[(int)index + 1] - roadVector[(int)index]) * pos;
		result.y = 2;

		return result;
	}

	else if(side == 1)
	{
		Point3D intermediate1 = roadVector[(int)index] + (rightVector[(int)index] - roadVector[(int)index]) * gradient;
		Point3D intermediate2 = roadVector[(int)index + 1] + (rightVector[(int)index + 1] - roadVector[(int)index] + 1) * gradient;

		Point3D result = intermediate1 + (intermediate2 - intermediate1) * pos;
		result.y = 2;

		return result;
	}

	else if(side == 2)
	{
		Point3D intermediate1 = roadVector[(int)index] + (leftVector[(int)index] - roadVector[(int)index]) * gradient;
		Point3D intermediate2 = roadVector[(int)index + 1] + (leftVector[(int)index + 1] - roadVector[(int)index] + 1) * gradient;

		Point3D result = intermediate1 + (intermediate2 - intermediate1) * pos;
		result.y = 2;

		return result;
	}
}

void Road::AddRoadObject(WorldObject* object)
{
	onRoadObjects.push_back(RoadWorldObjectLink(object,0));
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