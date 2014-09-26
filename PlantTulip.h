#pragma once
#include"WorldObject.h"
#include"Textures.h"
#include"FireBall.h"
#include"PlantHead.h"
#include"PlantLeaf.h"
class PlantTulip:public WorldObject, public Updatable
{
private:
	WorldObject *target;
	int contor;
	PlantHead *head;
	PlantLeaf *leaf;
	Scene* scene;
	
public:
	PlantTulip(Scene* scene, GLfloat width, GLfloat height, GLfloat length);
	~PlantTulip(void);
	void DrawObject();
	void DrawTulip();
	void SetTarget(WorldObject *target);
	void Update();
};
