#pragma once
#include "WorldObject.h"
#include "Mario.h"
#include "Particles.h"
#include"Item.h"
#include "Particles.h"

class FireBall:public WorldObject, public Updatable, public Item
{
private:
	GLfloat radius;
	double distanceTravelled;
	Particles *particles;
public:
	FireBall(GLfloat radius);
	~FireBall(void);
	void DrawObject();
	void Update();
	bool Function(Mario *mario);
};
