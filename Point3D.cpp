#include "Point3D.h"

Point3D::Point3D(float x,float y,float z):
x(x), y(y), z(z)
{}

Point3D Point3D::operator+(Point3D point)
{
	return Point3D(x+point.x,y+point.y,z+point.z);
}

Point3D Point3D::operator-(Point3D point)
{
	return Point3D(x-point.x,y-point.y,z-point.z);
}

Point3D Point3D::operator-()
{
	return Point3D(-x,-y,-z);
}

void Point3D::operator +=(Point3D point)
{
	*this = *this+point;
}

void Point3D::operator -=(Point3D point)
{
	*this = *this+point;
}

Point3D Point3D::operator*(float value)
{
	return Point3D(x*value,y*value,z*value);
}

Point3D Point3D::operator/(float value)
{
	return Point3D(x/value,y/value,z/value);
}	

float Point3D::operator*(Point3D point)
{
	return x*point.x+y*point.y+z*point.z;
}

Point3D Point3D::Scale(Point3D scale)
{
	return Point3D(x*scale.x,y*scale.y,z*scale.z);
}


bool Point3D::operator==(Point3D point)
{
	return point.x == x && point.y == y && point.z == z;
}

bool Point3D::operator!=(Point3D point)
{
	return point.x != x || point.y != y || point.z != z;
}

float Point3D::Magnitude()
{
	return sqrt(x*x+y*y+z*z);
}

Point3D Point3D::RotateX(float angle)
{
	float PI = 3.14159265359;
	return Point3D(x, y*cos(angle*PI/180) - z*sin(angle*PI/180), y*sin(angle*PI/180) + z*cos(angle*PI/180));
}

Point3D Point3D::RotateY(float angle)
{
	float PI = 3.14159265359;
	return Point3D(x*cos(angle*PI/180) - z*sin(angle*PI/180), y, x*sin(angle*PI/180) + z*cos(angle*PI/180));
}

Point3D Point3D::RotateZ(float angle)
{
	float PI = 3.14159265359;
	return Point3D(x*cos(angle*PI/180) - y*sin(angle*PI/180), x*sin(angle*PI/180) + y*cos(angle*PI/180),z);
}

Point3D Point3D::Normalize()
{
	float magnitude = Magnitude();
	if(magnitude == 0)
		return Point3D(0,0,0);
	return (*this)/magnitude;
}

float Point3D::AngleBetween(Point3D point)
{
	float PI = 3.14159265359;

	float dotProduct = ((*this)*point);

	float eq = dotProduct/((*this).Magnitude()*point.Magnitude());

	if(eq > 1 || eq < -1)
		return 0;

	return acos(eq)*180/PI;
}

istream& operator>>(istream& in, Point3D& point)
{
	return in>>point.x>>point.y>>point.z;
}

ostream& operator<<(ostream& out, Point3D point)
{
	return out<<point.x<<" "<<point.y<<" "<<point.z;
}


GLfloat GetRandomGLfloat(GLfloat min, GLfloat max)
{
	GLfloat range = max - min;
	GLfloat num = range * (rand()%100)/100.0;
	GLfloat sign=rand()%2;
	if(sign==0)
	{
		return (num + min);
	}

	return -(num + min);
	
}