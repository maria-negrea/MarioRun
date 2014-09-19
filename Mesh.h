#pragma once
#include <vector>
#include "WorldObject.h"
#include "Textures.h"
#include "AnimatedWorldObject.h"
#include "ColoredPoint3D.h"

#define PI 3.14

struct Triangle
{
	int p1,p2,p3, textureIndex;
	GLfloat u1, v1, u2, v2, u3, v3;

	Triangle(int p1 = 0, int p2 = 0, int p3 = 0, int textureIndex=0, GLfloat u1=0.0, GLfloat v1=0.0, GLfloat u2=0.0, GLfloat v2=0.0, GLfloat u3=0.0, GLfloat v3=0.0)
		:p1(p1),p2(p2),p3(p3), textureIndex(textureIndex), u1(u1), v1(v1), u2(u2), v2(v2), u3(u3), v3(v3)
	{
	}
};

class Mesh : public AnimatedWorldObject
{
protected:
	Point3D* vertices;
	Triangle* triangles;

	int verticesCount;
	int trianglesCount;
public:
	Mesh();
	Mesh(Point3D* vertices, Triangle* triangles, int verticesCount,int trianglesCount);
	void DrawObject();
	~Mesh();
};
