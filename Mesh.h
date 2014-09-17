#pragma once
#include <vector>
#include "WorldObject.h"
#include "Textures.h"
#include "AnimatedWorldObject.h"

#define PI 3.14

struct Triangle
{
	int p1,p2,p3;

	Triangle(int p1 = 0, int p2 = 0, int p3 = 0)
		:p1(p1),p2(p2),p3(p3)
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
	Mesh( Point3D* vertices, Triangle* triangles, int verticesCount,int trianglesCount);
	~Mesh();
};
