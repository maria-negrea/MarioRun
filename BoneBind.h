#pragma once
#include "WorldObject.h"

class BoneBind
{
	WorldObject* bone;
	vector<int> points;

	Point3D bindTranslate;
	Point3D bindRotate;

	Point3D GetTranslate();
	Point3D GetRotate();
public:
	BoneBind(WorldObject* bone,vector<int> points,Point3D bindTranslate,Point3D bindRotate);
	~BoneBind();

	void ModifyPoints(Point3D* points,Point3D* originPoints);
};
