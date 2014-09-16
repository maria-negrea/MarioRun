#pragma once
#include "Point3D.h"
#include<vector>

class WorldObject;

using namespace std;

class Collider
{
private:
	vector<Point3D> points;	
public:
	Collider(void);
	~Collider(void);

	void Affected(bool collision);
	static bool check(vector<Point3D> a, vector<Point3D> b);
};

#include "WorldObject.h"
