#pragma once
#include "WorldObject.h"

struct Triangle
{
	int p1,p2,p3;

	Triangle(int p1 = 0, int p2 = 0, int p3 = 0)
		:p1(p1),p2(p2),p3(p3)
	{
	}
};

class Mesh : public WorldObject
{
	Point3D* vertices;
	Triangle* triangles;

	int verticesCount;
	int trianglesCount;

	void DrawObject();
public:
	Mesh( Point3D* vertices, Triangle* triangles, int verticesCount,int trianglesCount);
	~Mesh();
};
