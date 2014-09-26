#pragma once
#include "AnimatedWorldObject.h"
#include "Textures.h"

class Box : public AnimatedWorldObject
{
	GLfloat sizeX,sizeY,sizeZ;
	void DrawObject();

	GLUquadricObj *quadratic;
public:
	Box(GLfloat sizeX = 1,GLfloat sizeY = 1,GLfloat sizeZ = 1);
	~Box();
};
