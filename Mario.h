#pragma once
#include "Mesh.h"
#include "WorldObject.h"

class Mario : public Mesh
{
public:
	Mario();
	~Mario();

	Point3D* MarioPoints();
	Triangle* MarioTriangles();
};
