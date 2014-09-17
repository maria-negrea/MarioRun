#pragma once
#include <math.h>

class Point3D
{
public:
	float x,y,z;

	Point3D(float x=0,float y=0,float z=0);

	Point3D operator+(Point3D point);
	Point3D operator-(Point3D point);
	Point3D operator-();
	void operator +=(Point3D point);
	Point3D operator*(float value);
	Point3D operator/(float value);
	float operator*(Point3D point);

	bool operator==(Point3D point);
	bool operator!=(Point3D point);

	float Magnitude();

	Point3D RotateX(float angle);
	Point3D RotateY(float angle);
	Point3D RotateZ(float angle);

	Point3D Normalize();
	float AngleBetween(Point3D point);
};