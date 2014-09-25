#pragma once
#include "PhysicsObject.h"
#include "Updatable.h"
#include "Input.h"
#include "Box.h"
#include "QuestionBlock.h"

enum MarioAnimations
{
	None,
	Run,
	Jump, 
	Hit, 
	Dead
};

class Mario : public PhysicsObject, public OnRoadObject
{
	void DrawObject();

	GLfloat forwardSpeed;
	GLfloat acceleration;
	GLfloat maxSpeed;
	bool isBig;
	bool bleep;
	bool invulnerable;
	bool deadMario;

	double time;
	double jumpForce;
	double dying;

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

	Box* upperArmRight;
	Box* lowerArmRight;
	Box* rightHand;
	Box* upperArmLeft;
	Box* lowerArmLeft;
	Box* leftHand;

	void RunAnimation();
	void JumpAnimation();
	void HitAnimation();
	void DeadAnimation();

	MarioAnimations animation;
public:
	Mario();
	~Mario();

	void MoveRight();
	void MoveLeft();

	void Update();
	void Jump();

	void Hit(Collision collision);
	void Damage();

	void Translate(Point3D translation);

	void SetSize();
	bool GetBleep();

	bool IsBig();

	bool GetInvulnerable();
	void SetInvulnerable();

	void SetDead();
	bool IsDead();

	void IncrementIndex();
};
