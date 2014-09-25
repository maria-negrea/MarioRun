#include<time.h>
#include "Road.h"
#include "Point2D.h"
#include "Segment2D.h"

Road::Road(void)
{
	srand(time(NULL));

	GLfloat width = 20;
	GLfloat length = 40;
	Point3D lastRoad(0, 0, -length/2);
	roadSize=20;

	Point3D lastCurve = Point3D(0,0,1);

	double angle = 10.234556;

	for(int i = 0; i < roadSize+2; i++)
	{
		Point3D newRoad = lastCurve.RotateY(angle);
		lastCurve = newRoad;

		if(i % 5 == 0)
			angle = rand() % 30 - 15;

		leftVector.push_back(newRoad.RotateY(-90.0)*width + lastRoad);
		rightVector.push_back(newRoad.RotateY(90.0)*width + lastRoad);

		roadVector.push_back(lastRoad);
		lastRoad += newRoad*length;
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
			if(i == onRoadObjects[j]->GetIndex())
				glColor3f(1.0,0.0,0.0);
		}

		glBegin(GL_QUADS);
			glVertex3f(leftVector[i].x, 0.01, leftVector[i].z);
			glVertex3f(rightVector[i].x, 0.01, rightVector[i].z);
			glVertex3f(rightVector[i + 1].x, 0.01, rightVector[i + 1].z);
			glVertex3f(leftVector[i + 1].x, 0.01, leftVector[i + 1].z);
		glEnd();
	}
}



#include<iostream>
using namespace std;

void Road::Update()
{
	for(unsigned i = 0; i<onRoadObjects.size();i++)
	{
		int index = onRoadObjects[i]->GetIndex();
		if(!IsOnIndex(onRoadObjects[i]))
		{
			if(index > 1)
			{
				onRoadObjects[i]->SetIndex(index-1);
			}

			while(!IsOnIndex(onRoadObjects[i]))
			{
				onRoadObjects[i]->IncrementIndex();
			}
		}
		if(onRoadObjects[i]->IsLinked())
		{
			SetOnRoadAngle(onRoadObjects[i]);
		}
	}
}

void Road::SetOnRoadAngle(OnRoadObject* onRoadObject)
{
	int roadIndex = onRoadObject->GetIndex();

	if(roadIndex <= roadSize)
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

		if(angle-onRoadObject->GetLastAngle() > 0.5)
		{
			cout<<angle-onRoadObject->GetLastAngle()<<endl;
		}
		onRoadObject->SetRotateY(angle);
		onRoadObject->SetLastAngle(angle);
	}
}

bool CheckInPoly(Point3D p3D1,Point3D p3D2,Point3D p3D3,Point3D p3D4,Point3D check3D, View perspective)
{
	Point2D p1 = Point2D(p3D1,perspective);
	Point2D p2 = Point2D(p3D2,perspective);
	Point2D p3 = Point2D(p3D3,perspective);
	Point2D p4 = Point2D(p3D4,perspective);

	Point2D check = Point2D(check3D,perspective);

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

bool Road::IsOnIndex(OnRoadObject* onRoadObject)
{
	int roadIndex = onRoadObject->GetIndex();

	if(roadIndex <= roadSize)
	{
		return CheckInPoly(rightVector[roadIndex],leftVector[roadIndex],leftVector[roadIndex+1],rightVector[roadIndex+1],onRoadObject->GetTranslate(),View::Up);
	}
	else
	{
		int g = 0;
	}
	return true;
}

Point3D Road::GetOnRoadPosition(Point3D point, GLfloat obstacleWidth)
{
	int indexZ= floor(point.z);	
	/*if(indexZ>19)
	{
		cout<<"jhhg"<<endl;
	}*/
	double posZ = point.z-indexZ;
	double posX = point.x;

	if(indexZ <= roadSize )
	{
		if(posX < 0)
		{
			posX = -posX;
		}
				
		if(point.x<0 && point.x-obstacleWidth/2<leftVector[indexZ].x)
		{
			point.x+=obstacleWidth/2;
		}
		if(point.x>0 && point.x+obstacleWidth/2>rightVector[indexZ].x)
		{
			point.x-=obstacleWidth/2;
		}
		Point3D intermediateZ = (roadVector[indexZ+1] - roadVector[indexZ]) * posZ;

		int index=indexZ;

		Point3D intermediateX;
		if(point.x<0)
		{
			intermediateX = (rightVector[index] - roadVector[indexZ]) * posX;
		}
		else
		{
			intermediateX = (leftVector[index] - roadVector[indexZ]) * posX;
		}

		Point3D result = roadVector[indexZ] + intermediateZ + intermediateX;

		if(result.x+obstacleWidth+2>leftVector[indexZ].x)
		{
			result.x-=obstacleWidth;
		}
		if(result.x-obstacleWidth-2>rightVector[indexZ].x)
		{
			result.x+=obstacleWidth;
		}
		return result;
	}
	else
	{
		int g = 0;
	}
	return Point3D();
}

void Road::AddRoadObject(OnRoadObject* object)
{
	onRoadObjects.push_back(object);
	object->SetRoad(this);
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

void Road::OffRoad(OnRoadObject* onRoadObject)
{
	GLfloat width = 19;
	int roadIndex = onRoadObject->GetIndex();

	Point3D reachPosition = onRoadObject->GetTranslate();

	Point3D rotationDirection = (roadVector[roadIndex+1] - roadVector[roadIndex]);
	Point3D relativObjPosition = (reachPosition-roadVector[roadIndex]);
	
	double angle = (rotationDirection).AngleBetween(Point3D(0,0,1));

	if((rotationDirection).x < 0)
	{
		angle = -angle;
	}

	relativObjPosition = relativObjPosition.RotateY(angle);
	if(relativObjPosition.x < -width)
	{
		relativObjPosition.x = -width;

	}
	if(relativObjPosition.x > width)
	{
		relativObjPosition.x = width;		
	}
	onRoadObject->SetTranslate(relativObjPosition.RotateY(-angle)+roadVector[roadIndex]);
}

GLfloat Road:: GetCurrentLength()
{
	return 0.0;
}

int Road:: GetRoadSize()
{
	return roadSize;
}