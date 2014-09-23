#pragma once

#include"PhysicsObject.h"
#include"Textures.h"
#include "Item.h"

class Mushroom : public PhysicsObject, public OnRoadObject, public Item
{
private:
	GLfloat speed;	
public:
	Mushroom(GLfloat width, GLfloat height, GLfloat size);
	~Mushroom(void);
	
	void Translate(Point3D translation);

	void DrawObject();
	void DrawMushroom();

	void Update();
	void Function(Mario *mario);
};

