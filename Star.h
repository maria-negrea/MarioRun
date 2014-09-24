#pragma once

#include "WorldObject.h"
#include "Textures.h"
#include "Updatable.h"
#include "Item.h"
#include "GlobalScore.h"
#include "OnRoadObject.h"

class Star : public PhysicsObject, public OnRoadObject, public Item
{
	GLfloat speed;
public:
	Star(GLfloat width, GLfloat height, GLfloat length);
	~Star(void);
	void DrawObject();
	void Update();
	bool Function(Mario *mario);
	void Translate(Point3D translation);
};
