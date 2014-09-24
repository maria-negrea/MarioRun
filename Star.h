#pragma once

#include "WorldObject.h"
#include "Textures.h"
#include "Updatable.h"
#include "Item.h"
#include "GlobalScore.h"
#include "OnRoadObject.h"

class Star : public OnRoadObject, public PhysicsObject, public Item
{
	GLfloat speed;
public:
	Star(GLfloat width, GLfloat height, GLfloat length);
	~Star(void);
	void DrawObject();
	void Update();
	void Function(Mario *mario);
	void Translate(Point3D translation);
};
