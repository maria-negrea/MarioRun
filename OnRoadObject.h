#pragma once
#include "WorldObject.h"

class Road;

class OnRoadObject : virtual public WorldObject
{
protected:
	int roadIndex;
	Road* road;
	double lastAngle;
	bool directionLink;
public:
	OnRoadObject(bool directionLink = true, int roadIndex = 0);
	~OnRoadObject();
	
	int GetIndex();

	void SetRoad(Road* road);

	void SetIndex(int index);
	virtual void IncrementIndex();

	void SetLastAngle(double angle);
	double GetLastAngle();
	bool IsLinked();
};

#include "Road.h"
