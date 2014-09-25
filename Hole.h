#pragma once
#include "WorldObject.h"
#include "Textures.h"
#include "Mario.h"
#include "Segment2D.h"
#include "Line.h"

class Hole: public WorldObject, public Updatable
{
	Point3D p1, p2, p3, p4;
	int textureIndex;
	bool CheckInPoly(Point3D p3D1,Point3D p3D2,Point3D p3D3,Point3D p3D4,Point3D check3D, View perspective);
	Mario* mario;
public:
	Hole(Mario* mario, Point3D p1, Point3D p2, Point3D p3, Point3D p4);
	void DrawObject();
	bool IsInside(Point3D point);
	void Update();
	~Hole(void);
};
