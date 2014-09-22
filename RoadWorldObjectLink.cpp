#include "WorldObject.h"
#include "RoadWorldObjectLink.h"
#include "Road.h"

RoadWorldObjectLink::RoadWorldObjectLink(WorldObject* object, int roadIndex)
{
	this->object = object;
	this->roadIndex = roadIndex;
}

RoadWorldObjectLink::~RoadWorldObjectLink(void)
{
}

WorldObject* RoadWorldObjectLink::GetObject()
{
	return object;
}

int RoadWorldObjectLink::GetIndex()
{
	return roadIndex;
}

void RoadWorldObjectLink::SetIndex(int index)
{
	this->roadIndex = index;
}

void RoadWorldObjectLink::IncrementIndex()
{
	++roadIndex;
}