#include "Road.h"
#include<time.h>

Road::Road(void)
{
	srand(time(NULL));

	Point3D lastRoad(0, 0, -10);
	Point3D currentRoad;

	double angle = 0;

	for(int i = 1; i < 1000; i++)
	{
		Point3D newRoad(0, 0, 10);

		newRoad = newRoad.RotateY(angle);
		if(i % 5 == 0)
			angle = rand() % 60 - 30;

		leftVector.push_back(newRoad.RotateY(-90) + lastRoad);
		rightVector.push_back(newRoad.RotateY(90) + lastRoad);

		roadVector.push_back(currentRoad);

		lastRoad = currentRoad;
		currentRoad += newRoad;
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
		glBegin(GL_QUADS);
			glVertex3f(leftVector[i].x, 0.1, leftVector[i].z);
			glVertex3f(rightVector[i].x, 0.1, rightVector[i].z);
			glVertex3f(rightVector[i + 1].x, 0.1, rightVector[i + 1].z);
			glVertex3f(leftVector[i + 1].x, 0.1, leftVector[i + 1].z);
		glEnd();
	}
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

vector<Point3D>Road::GetRoad()
{
	return roadVector;
}

vector<Point3D>Road::GetLeft()
{
	return leftVector;
}

vector<Point3D>Road::GetRight()
{
	return rightVector;
}