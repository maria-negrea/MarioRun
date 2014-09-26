#pragma once
#include "Indexable.h"
#include"Textures.h"
#include"WorldObject.h"
#include<math.h>

class Mountain:public WorldObject, public Indexable
{
public:
	Mountain(GLfloat width, GLfloat height, GLfloat length);
	~Mountain(void);
	void DrawObject();
};
