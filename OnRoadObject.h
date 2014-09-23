#pragma once
#include "WorldObject.h"

class Road;

class OnRoadObject : virtual public WorldObject
{
protected:
	int roadIndex;
	Road* road;
public:
	OnRoadObject(int roadIndex = 0);
	~OnRoadObject();
	
	int GetIndex();

	void SetRoad(Road* road);

	void SetIndex(int index);
	void IncrementIndex();
};

#include "Road.h"
