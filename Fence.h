#pragma once
#include"WorldObject.h"
#include"FencePart.h"
#include<vector>
#include "Indexable.h"

class Fence:public WorldObject, public Indexable
{
private:
	
	int size;
  
public:
	Fence(GLfloat width,GLfloat length,GLfloat height, int size);
	~Fence(void);
	void DrawObject();
};
