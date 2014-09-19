#pragma once
#include"WorldObject.h"
#include"Textures.h"
class PlantHead:public WorldObject
{
private:
	GLfloat size;
public:
	PlantHead(GLfloat width, GLfloat height, GLfloat size);
	~PlantHead(void);
	void DrawPlantHead();
	void DrawObject();
};
