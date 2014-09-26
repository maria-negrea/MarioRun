#pragma once
#include "Mesh.h"
#include "Updatable.h"

class Foot: public Mesh
{
protected:
	int mainTextureIndex;
public:
	Foot(GLfloat width, GLfloat height, GLfloat length, int mainTextureIndex);
	/*void DrawObject();*/
	~Foot(void);
};
