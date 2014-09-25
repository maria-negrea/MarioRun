#include "Mario.h"
#include "MarioCollider.h"
#include "Goomba.h"
#include "Box.h"

Point3D BackDirection()
{
	return Point3D((rand()%200-100)*0.01,(rand()%200-100)*0.01,-1);
}

Point3D Origin()
{
	return Point3D(0,0,0);
}

int DustGenerator() 
{
	return rand() % 4 + 1;
}

float RandomDirection()
{
	return rand()%360;
}

float VarySpeed()
{
	return rand()%300*0.01;
}

Mario::Mario():PhysicsObject(0.0)
{
	collider = new MarioCollider(this);
	hardCollider = true;
	road = NULL;

	jumpForce = 1.52;

	length = 2;
	width = 2;
	height = 9.5;

	forwardSpeed = 0;
	acceleration = 0.05;
	maxSpeed = 1;

	bleep = false;
	isBig = false;
	time = 0;
	invulnerable = false;

	pelvis = new Box(1,0.5,1);

	pelvis->Translate(Point3D(0,2.5,0));
	AddChild(pelvis);
	
	neck = new Box(0.25,0.25,0.25);
	head = new Box(1,1,1);
	head->Rotate(Point3D(0,0,0));
	body = new Box(1,1,1);

	upperArmLeft = new Box(0.4,0.6,0.4);
	upperArmLeft->Rotate(Point3D(180,0,0));
	upperArmLeft->Translate(Point3D(1.3,1.5,0));

	upperLegRight = new Box(0.4,0.5,0.4);
	upperLegRight->Rotate(Point3D(180,0,0));
	upperLegRight->Translate(Point3D(0.5,0.0,0));	

	lowerLegRight = new Box(0.4,0.5,0.4);
	lowerLegRight->Translate(Point3D(0,1.1,0));

	rightFoot = new Box(0.4,0.25,0.5);
	rightFoot->Translate(Point3D(0,1.1,0.125));

	upperLegLeft = new Box(0.4,0.5,0.4);
	upperLegLeft->Rotate(Point3D(180,0,0));
	upperLegLeft->Translate(Point3D(-0.5,0.0,0));	

	lowerLegLeft = new Box(0.4,0.5,0.4);
	lowerLegLeft->Translate(Point3D(0,1.1,0));

	leftFoot = new Box(0.4,0.25,0.5);
	leftFoot->Translate(Point3D(0,1.1,0.125));

	pelvis->AddChild(body);
	body->Translate(Point3D(0,1,0));
	body->AddChild(neck);
	body->AddChild(upperArmLeft);
	neck->Translate(Point3D(0,2,0));
	neck->AddChild(head);
	head->Translate(Point3D(0,0.5,0));

	pelvis->AddChild(upperLegRight);
	upperLegRight->AddChild(lowerLegRight);
	lowerLegRight->AddChild(rightFoot);

	pelvis->AddChild(upperLegLeft);
	upperLegLeft->AddChild(lowerLegLeft);
	lowerLegLeft->AddChild(leftFoot);

	dustTrail = NULL;

	RunAnimation();
}

Mario::~Mario()
{

}

void Mario::DrawObject()
{
}

void Mario::Jump()
{
	if(IsGrounded())
	{
		fallSpeed += 1.5;
	}
}


void Mario::RunAnimation()
{
	Animation pelvisAnimation;
	pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,200,0),pelvis->GetTranslate()));
	pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,160,0),pelvis->GetTranslate()));
	pelvis->SetAnimation(pelvisAnimation);

	Animation upperLegRightAnimation;
	upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0),upperLegRight->GetTranslate()));
	upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0),upperLegRight->GetTranslate()));
	upperLegRight->SetAnimation(upperLegRightAnimation);

	Animation lowerLegRightAnimation;
	lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-120,0,0),lowerLegRight->GetTranslate()));
	lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegRight->GetTranslate()));
	lowerLegRight->SetAnimation(lowerLegRightAnimation);

	Animation rightFootAnimation;
	rightFootAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),rightFoot->GetTranslate()));
	rightFootAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),rightFoot->GetTranslate()));
	rightFoot->SetAnimation(rightFootAnimation);

	Animation upperLegLeftAnimation;
	upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0),upperLegLeft->GetTranslate()));
	upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0),upperLegLeft->GetTranslate()));
	upperLegLeft->SetAnimation(upperLegLeftAnimation);

	Animation lowerLegLeftAnimation;
	lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));
	lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-120,0,0),lowerLegLeft->GetTranslate()));
	lowerLegLeft->SetAnimation(lowerLegLeftAnimation);
	
	Animation leftFootAnimation;
	leftFootAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),leftFoot->GetTranslate()));
	leftFootAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),leftFoot->GetTranslate()));
	leftFoot->SetAnimation(leftFootAnimation);
}

void Mario::JumpAnimation()
{
	
}


void Mario::Update()
{
	PhysicsObject::Update();

	if(scene != NULL)
	{
		if(dustTrail == NULL)
		{
			dustTrail = new Particles(BackDirection, 
				Origin, 
				DustGenerator, 
				Point3D(1,1,1),
				Point3D(0,0,0),
				RandomDirection, 
				NULL,
				VarySpeed,
				19);

			scene->AddObject(dustTrail);
		}
	}

	if(dustTrail != NULL)
	{
		dustTrail->SetTranslate(translate);
		dustTrail->SetRotate(rotate);
	}

	forwardSpeed += acceleration;
	if(forwardSpeed > maxSpeed)
		forwardSpeed = maxSpeed;

	Translate(GetForward()*forwardSpeed);

	if(Input::GetLeft())
		this->MoveLeft();

	if(Input::GetRight())
		this->MoveRight();

	if(bleep == true)
	{
		if(invulnerable == false && time < 3)
		{
			visible = !visible;
			time += 0.05;
		}
		else if(invulnerable == true && time <	10)
		{
			visible = !visible;
			time += 0.05;
		}
		else
		{
			visible = true;
			time = 0;
			bleep = false;
			invulnerable = false;
		}
	}
}

void Mario::Hit(Collision collision)
{
	Point3D direction = collision.GetDirection();

	if(direction.y > 0.8)
	{
		QuestionBlock *block = dynamic_cast<QuestionBlock*>(collision.GetHitObject());
		if(block != NULL)
			block->Hit();
	}
	else
	{
		if(direction.y < -0.8)
		{
			fallSpeed = 0;

			Goomba* goomba = dynamic_cast<Goomba*>(collision.GetHitObject());
			if(goomba != NULL)
			{
				fallSpeed = jumpForce*0.3;
				goomba->Damage();
			}
		}
		else
		{
			if(direction.AngleBetween(GetForward()) < 3)
			{
				forwardSpeed = -1;
				Damage();
			}
		}
	}
}

void Mario::MoveRight()
{
	Translate(GetRight()*-1);
}

void Mario::MoveLeft()
{
	Translate(GetRight()*1);
}


void Mario::Translate(Point3D translation)
{
	WorldObject::Translate(translation);
	if(road != NULL)
	{
		road->OffRoad(this);
	}
}

void Mario::SetSize()
{
	this->isBig = !this->isBig;

	if(isBig)
		this->Scale(Point3D(0.2, 0.2, 0.2));
	else
	{
		this->Scale(Point3D(-0.2, -0.2, -0.2));
		bleep = true;
	}
}

bool Mario::GetBleep()
{
	return bleep;
}

bool Mario::IsBig()
{
	return isBig;
}

void Mario::Damage()
{
	if(isBig)
	{
		isBig = false;
	}
	bleep = true;
}

void Mario::SetInvulnerable()
{
	invulnerable = true;
	bleep = true;
}

bool Mario::GetInvulnerable()
{
	return invulnerable;
}

void Mario::IncrementIndex()
{
	OnRoadObject::IncrementIndex();
	
}