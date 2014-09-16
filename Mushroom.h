#pragma once

#include"WorldObject.h"
#include"Textures.h"
class Mushroom:public WorldObject, public Updatable
{
private:
	GLfloat size;
	
public:
	Mushroom(GLfloat width, GLfloat height, GLfloat size);
	~Mushroom(void);
	void DrawObject();
	void DrawMushroom();
	void Update();
	//void Box(int textureIndex);
};
