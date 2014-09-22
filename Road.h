#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "Coin.h"
#include "Goomba.h"
#include "QuestionBlock.h"

class Road : public WorldObject, public Updatable
{ 
private:
	vector<Point3D> roadVector;
	vector<Point3D> leftVector;
	vector<Point3D> rightVector;

	WorldObject* onRoadObject;
	int roadIndex;
	int roadSize;

	bool IsOnIndex();
	void SetOnRoadAngle();
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
	
	void Update();
};
