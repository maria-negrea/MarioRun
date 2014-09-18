#pragma once

#include"PhysicsObject.h"
#include"Textures.h"
class Mushroom:public PhysicsObject
{
private:
	GLfloat size;
	GLfloat speed;
	
public:
	Mushroom(GLfloat width, GLfloat height, GLfloat size);
	~Mushroom(void);
	void DrawObject();
	void DrawMushroom();
	void Update();
	//void Box(int textureIndex);
};
