#pragma once
#include "PhysicsObject.h"
#include "Updatable.h"

class Mario : public PhysicsObject
{
	void DrawObject();
public:
	Mario();
	~Mario();

	void MoveRight();
	void MoveLeft();

	void Update();
	void Jump();
};
