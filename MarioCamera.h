#pragma once
#include "Camera.h"
#include "WorldObject.h"

class MarioCamera : public Camera, public Updatable
{
	WorldObject* follow;
public:
	MarioCamera(WorldObject* follow);
	~MarioCamera();

	void Update();
};
