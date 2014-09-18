#pragma once
#include "PhysicsObject.h"
#include "Updatable.h"
#include "Road.h"
#include "Input.h"
#include "Box.h"

class Mario : public PhysicsObject
{
	void DrawObject();

	GLfloat forwardSpeed;
	GLfloat acceleration;
	GLfloat maxSpeed;
public:
	Mario();
	~Mario();

	void MoveRight();
	void MoveLeft();

	void Update();
	void Jump();

	void Hit(Collision collision);
};
