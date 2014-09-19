#include "Mario.h"
#include "MarioCollider.h"
#include "Box.h"


Mario::Mario()
{
	collider = new MarioCollider(this);

	length = 2;
	width = 2;
	height = 9.5;

	forwardSpeed = 0;
	acceleration = 0.05;
	maxSpeed = 1;

	bleep = false;
	isBig = false;
	time = 0;

	Box* pelvis = new Box(1,0.5,1);

	pelvis->Translate(Point3D(0,2.5,0));
	AddChild(pelvis);
	
	Box* neck = new Box(0.25,0.25,0.25);
	Box* head = new Box(1,1,1);
	head->Rotate(Point3D(0,0,0));
	Box* body = new Box(1,1,1);

	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,200,0),pelvis->GetTranslate()));
	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,160,0),pelvis->GetTranslate()));

	Box* upperLegRight = new Box(0.4,0.5,0.4);
	upperLegRight->Rotate(Point3D(180,0,0));
	upperLegRight->Translate(Point3D(0.5,0.0,0));	

	upperLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0),upperLegRight->GetTranslate()));
	upperLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0),upperLegRight->GetTranslate()));

	Box* lowerLegRight = new Box(0.4,0.5,0.4);
	lowerLegRight->Translate(Point3D(0,1.1,0));

	lowerLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(-120,0,0),lowerLegRight->GetTranslate()));
	lowerLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegRight->GetTranslate()));

	Box* rightFoot = new Box(0.4,0.25,0.5);
	rightFoot->Translate(Point3D(0,1.1,0.125));

	rightFoot->AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),rightFoot->GetTranslate()));
	rightFoot->AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),rightFoot->GetTranslate()));

	Box* upperLegLeft = new Box(0.4,0.5,0.4);
	upperLegLeft->Rotate(Point3D(180,0,0));
	upperLegLeft->Translate(Point3D(-0.5,0.0,0));	

	upperLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0),upperLegLeft->GetTranslate()));
	upperLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0),upperLegLeft->GetTranslate()));

	Box* lowerLegLeft = new Box(0.4,0.5,0.4);
	lowerLegLeft->Translate(Point3D(0,1.1,0));

	lowerLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));
	lowerLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(-120,0,0),lowerLegLeft->GetTranslate()));

	Box* leftFoot = new Box(0.4,0.25,0.5);
	leftFoot->Translate(Point3D(0,1.1,0.125));

	leftFoot->AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),leftFoot->GetTranslate()));
	leftFoot->AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),leftFoot->GetTranslate()));


	pelvis->AddChild(body);
	body->Translate(Point3D(0,1,0));
	body->AddChild(neck);
	neck->Translate(Point3D(0,2,0));
	neck->AddChild(head);
	head->Translate(Point3D(0,0.5,0));

	pelvis->AddChild(upperLegRight);
	upperLegRight->AddChild(lowerLegRight);
	lowerLegRight->AddChild(rightFoot);

	pelvis->AddChild(upperLegLeft);
	upperLegLeft->AddChild(lowerLegLeft);
	lowerLegLeft->AddChild(leftFoot);
}

Mario::~Mario()
{

}

void Mario::DrawObject()
{
}

void Mario::Update()
{
	PhysicsObject::Update();
	
	forwardSpeed += acceleration;
	if(forwardSpeed > maxSpeed)
		forwardSpeed = maxSpeed;

	//Translate(GetForward()*forwardSpeed);

	if(Input::GetLeft())
		this->MoveLeft();

	if(Input::GetRight())
		this->MoveRight();

	if(bleep == true)
	{
		if(time < 3)
		{
			visible = !visible;
			time += 0.05;
		}
		else
		{
			visible = true;
			time = 0;
			bleep = false;
		}
	}
}

void Mario::Jump()
{
	if(IsGrounded())
	{
		fallSpeed += 1.5;
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
	if(direction.y < -0.8)
	{
		fallSpeed = 0;
	}
	else
	{
		if(direction.AngleBetween(GetForward()) < 5)
		{
			forwardSpeed = -1;
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