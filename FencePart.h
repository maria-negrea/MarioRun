#pragma once
#include"WorldObject.h"
class FencePart:public WorldObject
{
public:
	FencePart(GLfloat width, GLfloat height, GLfloat length);
	~FencePart(void);
	void DrawFence();
	void DrawObject();
};
