#pragma once
#include "Point3D.h"
#include "Collision.h"
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

	virtual void Hit(Collision collision);

	void Affected(Collision collision);
	static Point3D check(vector<Point3D> a, vector<Point3D> b);
};

#include "WorldObject.h"
