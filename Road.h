#pragma once

#include "WorldObject.h"
#include "Updatable.h"

class Road : public WorldObject, public Updatable
{ 
private:
	vector<Point3D> roadVector;
	vector<Point3D> leftVector;
	vector<Point3D> rightVector;

	WorldObject* onRoadObject;
	int roadIndex;

	bool IsOnIndex();
public:
	Road(void);
	~Road(void);
	void DrawObject();

	Point3D GetCoinPoint(double index, double gradient, int side);

	Point3D GetOnRoadPosition();

	vector<Point3D> GetRoad();
	vector<Point3D> GetLeft();
	vector<Point3D> GetRight();

	void SetRoadObject(WorldObject* object);
	void Update();
};
