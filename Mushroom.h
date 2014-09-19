#pragma once

#include"PhysicsObject.h"
#include"Textures.h"
#include "Item.h"

class Mushroom : public PhysicsObject//, public Item
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
	void Function(Mario *mario);
};

