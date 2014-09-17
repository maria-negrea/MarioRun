#pragma once

#include"WorldObject.h"

class Road : public WorldObject
{ 
private:
	vector<Point3D> roadVector;
	vector<Point3D> leftVector;
	vector<Point3D> rightVector;
public:
	Road(void);
	~Road(void);
	void DrawObject();
	Point3D GetCoinPoint(double index, double gradient, int side);
	vector<Point3D> GetRoad();
	vector<Point3D> GetLeft();
	vector<Point3D> GetRight();
};
