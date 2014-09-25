#pragma once

#include "Updatable.h"
#include "OnRoadObject.h"
#include "Textures.h"

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

	GLfloat width;
	GLfloat length;
	Point3D lastRoad;
	Point3D lastCurve;

    double angle;

public:
	bool isNewRoad;
	Road(void);
	~Road(void);
	void DrawObject();
	void GenerateRoad();
	Point3D GetOnRoadPosition(Point3D point, GLfloat obstacleWidth);	
	vector<Point3D> GetRoad();
	vector<Point3D> GetLeft();
	vector<Point3D> GetRight();
	void SetRoadObject(WorldObject* object);
	int GetRoadSize();

	void RemoveObject(OnRoadObject* object);

	void AddRoadObject(OnRoadObject* object);
	void Update();

	void OffRoad(OnRoadObject* onRoadObject);
	GLfloat GetCurrentLength();
};

