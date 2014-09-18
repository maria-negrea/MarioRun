#pragma once
#include "Head.h"
#include "Torso.h"
#include "Foot.h"

class Goomba: public WorldObject, public Updatable
{
protected:
	WorldObject* target;
	GLfloat speed;
public:
	Goomba(void);
	void DrawObject();
	void Update();
	void SetTarget(WorldObject* target);
	~Goomba(void);
};
