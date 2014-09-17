#pragma once
#include"WorldObject.h"
class Plant:public WorldObject
{
GLfloat size;

public:
	Plant(GLfloat width, GLfloat height, GLfloat size);
	~Plant(void);
	void DrawObject();
};
