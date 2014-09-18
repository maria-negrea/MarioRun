#pragma once
#include"WorldObject.h"
#include"Textures.h"
class PlantLeaf:public WorldObject
{
private:
	GLfloat size;
public:
	PlantLeaf(GLfloat width, GLfloat height, GLfloat size);
	~PlantLeaf(void);
	void DrawObject();
};
