#pragma once
#include "WorldObject.h"
#include "Updatable.h"

class PhysicsObject : public WorldObject, public Updatable
{
protected:
	GLfloat fallSpeed;
public:
	PhysicsObject(void);
	~PhysicsObject(void);

	bool IsGrounded();
	virtual void Update();
};
