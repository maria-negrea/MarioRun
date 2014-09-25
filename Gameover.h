#pragma once
#include"WorldObject.h"
#include "Updatable.h"
class Gameover: public WorldObject, public Updatable
{
public:
	Gameover(GLfloat width, GLfloat height, GLfloat length);
	~Gameover(void);
	void DrawObject();
	void Update();
};
