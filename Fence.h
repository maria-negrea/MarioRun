#pragma once
#include"WorldObject.h"
#include"FencePart.h"
#include<vector>

class Fence:public WorldObject
{
private:
	
	int size;
  
public:
	Fence(GLfloat width,GLfloat length,GLfloat height, int size);
	~Fence(void);
	void DrawObject();
};
