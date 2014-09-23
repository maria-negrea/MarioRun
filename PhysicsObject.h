#pragma once
#include "WorldObject.h"
#include "Updatable.h"

class PhysicsObject : virtual public WorldObject, public Updatable
{
protected:
	GLfloat fallSpeed;
	bool isGrounded;
	double bounce;
public:
	PhysicsObject(double bounce = 0.9);
	~PhysicsObject();

	bool IsGrounded();
	virtual void Update();
};
