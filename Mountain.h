#pragma once


#include"Textures.h"
#include"WorldObject.h"
#include<math.h>
class Mountain:public WorldObject
{
public:
	Mountain(GLfloat width, GLfloat height, GLfloat length);
	~Mountain(void);
	void DrawObject();
};
