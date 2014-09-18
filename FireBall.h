#pragma once
#include"WorldObject.h"
#include"Mario.h"

class FireBall:public WorldObject, public Updatable
{private:
GLfloat radius;
public:
	FireBall(GLfloat radius);
	~FireBall(void);
	void DrawObject();
	void Update();
	void Function(Mario *mario);
};
