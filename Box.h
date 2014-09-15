#pragma once
#include "AnimatedWorldObject.h"

class Box : public AnimatedWorldObject
{
	GLfloat sizeX,sizeY,sizeZ;
	void DrawObject();
public:
	Box(GLfloat sizeX = 1,GLfloat sizeY = 1,GLfloat sizeZ = 1);
	~Box();
};
