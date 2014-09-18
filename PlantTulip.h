#pragma once
#include"WorldObject.h"
#include"Textures.h"
#include"FireBall.h"
class PlantTulip:public WorldObject, public Updatable
{
private:
	GLfloat size;
	WorldObject *target;
	int contor;
	
public:
	PlantTulip(GLfloat width, GLfloat height, GLfloat size);
	~PlantTulip(void);
	void DrawObject();
	void SetTarget(WorldObject *target);
	void Update();
};
