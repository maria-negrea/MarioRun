#pragma once
#include <vector>
#include "WorldObject.h"

typedef int Triangle[3];

class Mesh : public WorldObject
{
	vector<Point3D> vertices;
	vector<Triangle> triangles;

	void DrawObject();
public:
	Mesh();
	Mesh( vector<Point3D> vertices, vector<Triangle> triangles);
	~Mesh();
};
