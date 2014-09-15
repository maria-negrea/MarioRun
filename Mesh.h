#pragma once
#include <vector.h>
#include "WorldObject.h"

typedef int Triangle[3];

class Mesh : public WorldObject
{
	vector<Point3D> vertices;
	vector<Triangle> triangles;

	void DrawObject();
public:
	Mesh( vector<Point3D> vertices, vector<Triangle> triangles);
	~Mesh();
};
