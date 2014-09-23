#pragma once

#include "WorldObject.h"
#include "Updatable.h"

class OnRoadObject;

class Road : public WorldObject, public Updatable
{ 
private:
	vector<Point3D> roadVector;
	vector<Point3D> leftVector;
	vector<Point3D> rightVector;

	vector<OnRoadObject*> onRoadObjects;

	bool IsOnIndex(OnRoadObject* onRoadObject);
	void SetOnRoadAngle(OnRoadObject* onRoadObject);
public:
	Road(void);
	~Road(void);
	void DrawObject();

	Point3D GetCoinPoint(double index, double gradient, int side);

	vector<Point3D> GetRoad();
	vector<Point3D> GetLeft();
	vector<Point3D> GetRight();

	void AddRoadObject(OnRoadObject* object);
	void Update();

	Point3D OffRoad(OnRoadObject* onRoadObject);
};

#include "OnRoadObject.h"