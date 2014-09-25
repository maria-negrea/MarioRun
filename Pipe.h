#pragma once

#include "WorldObject.h"
#include "Textures.h"
#include "PlantTulip.h"

class Pipe : public WorldObject
{
	PlantTulip* plant;
public:
	Pipe(GLfloat width, GLfloat height, GLfloat length);
	~Pipe(void);
	void SetTarget(WorldObject* target);
	void DrawObject();
};
