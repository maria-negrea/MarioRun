#pragma once
#include <iostream>
#ifdef __unix || __unix__
 #include <GL/glut.h>
#else
 #include <glut.h>
#endif
#include <math.h>
#include <vector>

using namespace std;

struct Point3D
{
	GLfloat x,y,z;

	Point3D(GLfloat x=0,GLfloat y=0,GLfloat z=0):
	x(x), y(y), z(z)
	{}

	Point3D operator+(Point3D point)
	{
		return Point3D(x+point.x,y+point.y,z+point.z);
	}

	Point3D operator-(Point3D point)
	{
		return Point3D(x-point.x,y-point.y,z-point.z);
	}

	void operator +=(Point3D point)
	{
		*this = *this+point;
	}

	Point3D operator*(GLfloat value)
	{
		return Point3D(x*value,y*value,z*value);
	}

	Point3D operator/(GLfloat value)
	{
		return Point3D(x/value,y/value,z/value);
	}	

	GLfloat operator*(Point3D point)
	{
		return x*point.x+y*point.y+z*point.z;
	}

	GLfloat Magnitude()
	{
		return sqrt(x*x+y*y+z*z);
	}

	Point3D RotateX(GLfloat angle)
	{
		GLfloat PI = 3.14159265359;
		return Point3D(x, y*cos(angle*PI/180) - z*sin(angle*PI/180), y*sin(angle*PI/180) + z*cos(angle*PI/180));
	}

	Point3D RotateY(GLfloat angle)
	{
		GLfloat PI = 3.14159265359;
		return Point3D(x*cos(angle*PI/180) - z*sin(angle*PI/180), y, x*sin(angle*PI/180) + z*cos(angle*PI/180));
	}

	Point3D RotateZ(GLfloat angle)
	{
		GLfloat PI = 3.14159265359;
		return Point3D(x*cos(angle*PI/180) - y*sin(angle*PI/180), x*sin(angle*PI/180) + y*cos(angle*PI/180),z);
	}

	Point3D Normalize()
	{
		GLfloat magnitude = Magnitude();
		if(magnitude == 0)
			return Point3D(0,0,0);
		return (*this)/magnitude;
	}

	float AngleBetween(Point3D point)
	{
		float PI = 3.14159265359;

		float dotProduct = ((*this)*point);
		
		float eq = dotProduct/(Magnitude()*point.Magnitude());
		if(eq > 1.0 || eq < -1.0)
			return 0.0;

		return acos(eq)*180.0/PI;
	}
};

class WorldObject
{
protected:
	virtual void DrawObject() = 0;

	void ModifyPerspective();
	void ModifyPerspectiveBack();

	void ParentPerspective();
	void ParentPerspectiveBack();

	Point3D rotate;
	Point3D translate;
	
	vector<WorldObject*> children;
	WorldObject* parent;

public:
	GLfloat length, width, height; // OZ, OX and OY
	WorldObject(GLfloat W = 0.0, GLfloat H = 0.0,GLfloat X = 0.0, GLfloat Y = 0.0, GLfloat Z = 0.0);
	~WorldObject();

	void Translate(Point3D);
	void Rotate(Point3D);

	void Draw();

	Point3D GetForward();
	Point3D GetTranslate();
	Point3D GetRight();

	vector<Point3D> GetBoundingBox();

	Point3D GetRotate();

	void AddChild(WorldObject* child);

	int ChildrenCount();
	WorldObject* GetChild(int i);
	GLfloat AngleBetween(WorldObject* target);
};
