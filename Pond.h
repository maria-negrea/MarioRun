#pragma once
#include "WorldObject.h"
#include "Updatable.h"
#include "Scene.h"

class Pond : public WorldObject, public Updatable
{
private:
	void DrawObject();
	Scene *scene;
	int life, step;
public:
	Pond(Scene *scene);
	~Pond();
	void Update();
};
