#pragma once
#include "WorldObject.h"
#include"Mountain.h"
#include "Indexable.h"

class FullMountain:public WorldObject, public Indexable
{
public:
	FullMountain(GLfloat width, GLfloat height,GLfloat length) ;
	~FullMountain(void);
	void DrawObject();
};
