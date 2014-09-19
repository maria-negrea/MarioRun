#pragma once
#include "WorldObject.h"
#include "Mario.h"
#include "Particles.h"

class FireBall:public WorldObject, public Updatable
{
private:
	GLfloat radius;
	Particles *particles;
public:
	FireBall(GLfloat radius);
	~FireBall(void);
	void DrawObject();
	void Update();
	void Function(Mario *mario);
};
