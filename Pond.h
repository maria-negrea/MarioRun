#pragma once
#include "Updatable.h"
#include "Scene.h"
#include "CutoutObject.h"

class Pond : public CutoutObject, public Updatable
{
private:
	void DrawObject();
	GLfloat life;
public:
	Pond();
	~Pond();
	void Update();
};
