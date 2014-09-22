#pragma once

#include "WorldObject.h"
#include "Updatable.h"

class RoadWorldObjectLink;

class Road : public WorldObject, public Updatable
{ 
private:
	vector<Point3D> roadVector;
	vector<Point3D> leftVector;
	vector<Point3D> rightVector;

	vector<RoadWorldObjectLink> onRoadObjects;

	bool IsOnIndex(RoadWorldObjectLink onRoadObject);
	void SetOnRoadAngle(RoadWorldObjectLink onRoadObject);
public:
	Road(void);
	~Road(void);
	void DrawObject();

	Point3D GetCoinPoint(double index, double gradient, int side);

	vector<Point3D> GetRoad();
	vector<Point3D> GetLeft();
	vector<Point3D> GetRight();

	void AddRoadObject(WorldObject* object);
	void Update();
};

#include "RoadWorldObjectLink.h"