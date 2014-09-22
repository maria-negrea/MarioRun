#pragma once
#include "PhysicsObject.h"
#include "Updatable.h"
#include "Input.h"
#include "Box.h"
#include "QuestionBlock.h"

class Mario : public PhysicsObject
{
	void DrawObject();

	GLfloat forwardSpeed;
	GLfloat acceleration;
	GLfloat maxSpeed;
	bool isBig;
	bool bleep;

	double time;

	Box* pelvis;
	Box* neck;
	Box* head;
	Box* body;
	Box* upperLegRight;
	Box* lowerLegRight;
	Box* rightFoot;
	Box* upperLegLeft;
	Box* lowerLegLeft;
	Box* leftFoot;

	void RunAnimation();
	void JumpAnimation();
public:
	Mario();
	~Mario();

	void MoveRight();
	void MoveLeft();

	void Update();
	void Jump();

	void Hit(Collision collision);

	void SetSize();
	bool GetBleep();

	bool IsBig();
};
