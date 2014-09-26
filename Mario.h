#pragma once
#include "PhysicsObject.h"
#include "Updatable.h"
#include "Input.h"
#include "Box.h"
#include "QuestionBlock.h"
#include "Environmental.h"
#include "Particles.h"
#include "Mesh.h"

enum MarioAnimations
{
	None,
	Run,
	Jump, 
	Hit, 
	Dead, 
	SpecialRun,
	Drown, 
	Slide,
	Wave
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
	bool drown;

	double dying;

	double time;
	double jumpForce;

	bool startGame;


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
	Mesh* mesh;

	Particles* dustTrail;
	void RunAnimation();
	void JumpAnimation();
	void HitAnimation();
	void DeadAnimation();
	void SpecialRunAnimation();
	void DrownAnimation();
	void SlideAnimation();
	void WaveAnimation();

	MarioAnimations animation;
	Environmental* environment;
public:
	Mario(Environmental* enviroment);
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

	void SetDrown();
	void StartGame();
	bool GameStatus();
	bool IsDying();

	void IncrementIndex();
};
