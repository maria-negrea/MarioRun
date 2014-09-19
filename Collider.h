#pragma once
#include "Point3D.h"
#include<vector>

class Collision;
class WorldObject;

using namespace std;

class Collider
{
	float Min(float x,float y);

	WorldObject* object;
public:
	Collider(WorldObject* object);
	~Collider(void);

	virtual void Hit(Collision collision);

	void Affected(Collision collision);
	Collision Check(WorldObject* other);
};

#include "WorldObject.h"
#include "Collision.h"
