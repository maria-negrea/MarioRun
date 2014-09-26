#pragma once
#include "Updatable.h"
#include "Scene.h"
#include "CutoutObject.h"

class Pond : public CutoutObject, public Updatable
{
private:
	void DrawObject();
	GLfloat life;
	int textureIndex;
public:
	Pond(int textureIndex);
	~Pond();
	void Update();
};
