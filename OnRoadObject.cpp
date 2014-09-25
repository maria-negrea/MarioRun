#include "OnRoadObject.h"
#include "Road.h"

OnRoadObject::OnRoadObject(bool directionLink, int roadIndex)
{
	this->roadIndex = roadIndex;
	this->directionLink = directionLink;
}

OnRoadObject::~OnRoadObject(void)
{
}

int OnRoadObject::GetIndex()
{
	return roadIndex;
}

void OnRoadObject::SetIndex(int index)
{
	this->roadIndex = index;
}

void OnRoadObject::IncrementIndex()
{
	++roadIndex;
}

void OnRoadObject::SetRoad(Road* road)
{
	this->road = road;
}

void OnRoadObject::SetLastAngle(double angle)
{
	this->lastAngle = angle;
}

double OnRoadObject::GetLastAngle()
{
	return lastAngle;
}

bool OnRoadObject::IsLinked()
{
	return directionLink;
}