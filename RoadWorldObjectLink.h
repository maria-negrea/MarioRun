#pragma once
#include "WorldObject.h"

class RoadWorldObjectLink
{
	WorldObject *object;
	int roadIndex;
public:
	RoadWorldObjectLink(WorldObject* object, int roadIndex);
	~RoadWorldObjectLink();
	
	int GetIndex();
	void SetIndex(int index);
	WorldObject* GetObject();

	void IncrementIndex();
};
