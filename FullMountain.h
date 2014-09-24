#pragma once
#include "WorldObject.h"
#include"Mountain.h"
class FullMountain:public WorldObject
{
public:
	FullMountain(GLfloat width, GLfloat height,GLfloat length) ;
	~FullMountain(void);
	void DrawObject();
};
