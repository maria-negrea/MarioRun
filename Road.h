#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "Coin.h"
#include "Goomba.h"
#include "QuestionBlock.h"

class RoadWorldObjectLink;

class Road : public WorldObject, public Updatable
{ 
private:
	vector<Point3D> roadVector;
	vector<Point3D> leftVector;
	vector<Point3D> rightVector;
	vector<RoadWorldObjectLink> onRoadObjects;

	WorldObject* onRoadObject;
	int roadIndex;
	int roadSize;

	bool IsOnIndex(RoadWorldObjectLink onRoadObject);
	void SetOnRoadAngle(RoadWorldObjectLink onRoadObject);
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

	void AddRoadObject(WorldObject* object);
	void Update();
};

#include "RoadWorldObjectLink.h"
