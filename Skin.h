#pragma once
#include "Mesh.h"
#include "BoneBind.h"

class Skin : public WorldObject
{
	Point3D* vertices;
	Triangle* triangles;

	Point3D* printVertices;
	
	void DrawObject();

	int verticesCount;
	int trianglesCount;

	vector<BoneBind> binds;
public:
	Skin(char* file, bool symmetry);
	~Skin();

	void AddBind(WorldObject* bone, vector<int> points);
};
