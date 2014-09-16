#pragma once
#include "WorldObject.h"
#include <vector>

class Collider
{
private:
	vector<Point3D> points;	
public:
	Collider(void);
	~Collider(void);
	void AddPoint(Point3D x);
	vector<Point3D> GetPoints();
	static bool check(vector<Point3D> a, vector<Point3D> b);
};
