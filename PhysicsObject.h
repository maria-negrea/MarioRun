#pragma once
#include "WorldObject.h"
#include "Updatable.h"

class PhysicsObject : public WorldObject, public Updatable
{
protected:
	GLfloat fallSpeed;
public:
	PhysicsObject();
	~PhysicsObject();

	bool IsGrounded();
	virtual void Update();
};
