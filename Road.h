#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "Coin.h"
#include "Goomba.h"
#include "QuestionBlock.h"

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

	int roadSize;
public:
	Road(void);
	~Road(void);
	void DrawObject();
	Point3D GetOnRoadPosition(Point3D point, GLfloat obstacleWidth);	
	vector<Point3D> GetRoad();
	vector<Point3D> GetLeft();
	vector<Point3D> GetRight();
	void SetRoadObject(WorldObject* object);
	int GetRoadSize();

	void AddRoadObject(OnRoadObject* object);
	void Update();

	void OffRoad(OnRoadObject* onRoadObject);
	GLfloat GetCurrentLength();
};

#include "OnRoadObject.h"