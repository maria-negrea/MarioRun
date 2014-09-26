#pragma once
#include "Indexable.h"
#include "WorldObject.h"
#include "Textures.h"
#include "PlantTulip.h"

class Pipe : public WorldObject, public Indexable
{
	PlantTulip* plant;
public:
	Pipe(GLfloat width, GLfloat height, GLfloat length);
	~Pipe(void);
	void SetTarget(WorldObject* target);
	void DrawObject();
};
