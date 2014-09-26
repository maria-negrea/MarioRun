#include "Mario.h"
#include "MarioCollider.h"
#include "Goomba.h"
#include "Box.h"
#include "Skin.h"
#include <fstream>

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

Mario::Mario():PhysicsObject(0.0),OnRoadObject(true)
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
	deadMario = false;

	dying = 0;

	pelvis = new Box(1,0.5,1);

	pelvis->Translate(Point3D(0,2.5,0));
	AddChild(pelvis);
	
	neck = new Box(0.25,0.25,0.25);
	head = new Box(1,1,1);
	head->Rotate(Point3D(0,0,0));
	body = new Box(1,1,1);
   
    //Hands
     upperArmRight=new Box(0.4,0.6,0.4);
	 upperArmRight->Translate(Point3D(1.4,1.2,0));

	 lowerArmRight=new Box(0.4,0.6,0.4);
	 lowerArmRight->Translate(Point3D(0,1.2,0.));

     rightHand=new Box(0.4,0.25,0.5);
	 rightHand->Translate(Point3D(0,0.85,0));


	 upperArmLeft=new Box(0.4,0.6,0.4);
	 upperArmLeft->Translate(Point3D(-1.4,1.2,0));

	 lowerArmLeft=new Box(0.4,0.6,0.4);
	 lowerArmLeft->Translate(Point3D(0,1.2,0.));

     leftHand=new Box(0.4,0.25,0.5);
	 leftHand->Translate(Point3D(0,0.85,0));
	 
	//Legs
	upperLegRight = new Box(0.4,0.5,0.4);
	upperLegRight->Rotate(Point3D(180,0,0));
	upperLegRight->Translate(Point3D(0.5,0.0,0));	


	lowerLegRight = new Box(0.4,0.5,0.4);
	lowerLegRight->Translate(Point3D(0,1.1,0));

	rightFoot = new Box(0.4,0.25,0.5);
	rightFoot->Translate(Point3D(0,1.1,0.125));

	upperLegLeft = new Box(0.4,0.5,0.4);
	//upperLegLeft->Rotate(Point3D(180,0,0));
	upperLegLeft->Translate(Point3D(-0.5,0.0,0));	

	lowerLegLeft = new Box(0.4,0.5,0.4);
	lowerLegLeft->Translate(Point3D(0,1.1,0));

	leftFoot = new Box(0.4,0.25,0.5);
	leftFoot->Translate(Point3D(0,1.1,0.125));

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

	dustTrail = NULL;

	body->AddChild(upperArmRight);
	upperArmRight->AddChild(lowerArmRight);
	lowerArmRight->AddChild(rightHand);

	body->AddChild(upperArmLeft);
	upperArmLeft->AddChild(lowerArmLeft);
	lowerArmLeft->AddChild(leftHand);

	mesh = NULL;

	head->SetTranslate(Point3D(0,-0.3,0));
	neck->SetTranslate(Point3D(0,3.12,0.78));
	upperArmRight->SetTranslate(Point3D(-1.2,2.28,0.42));
	lowerArmRight->SetTranslate(Point3D(-1.5,0,0));
	rightHand->SetTranslate(Point3D(-1.26,0,0));
	upperArmLeft->SetTranslate(Point3D(1.2,2.28,0.42));
	lowerArmLeft->SetTranslate(Point3D(1.5,0,0));
	leftHand->SetTranslate(Point3D(1.26,0,0));
	upperLegRight->SetTranslate(Point3D(-0.72,-0.6,0));
	lowerLegRight->SetTranslate(Point3D(0,-1.02,0.06));
	rightFoot->SetTranslate(Point3D(0,-1.08,0.6));
	upperLegLeft->SetTranslate(Point3D(0.72,-0.6,0));
	lowerLegLeft->SetTranslate(Point3D(0,-1.02,0.06));
	leftFoot->SetTranslate(Point3D(0,-1.08,0.6));
	body->SetTranslate(Point3D(0,0,0));
	pelvis->SetTranslate(Point3D(0,-3.48,0.48));

	head->SetRotate(Point3D(0,0,0));
	neck->SetRotate(Point3D(0,0,0));
	upperArmRight->SetRotate(Point3D(0,0,0));
	lowerArmRight->SetRotate(Point3D(0,0,0));
	rightHand->SetRotate(Point3D(0,0,0));
	upperArmLeft->SetRotate(Point3D(0,0,0));
	lowerArmLeft->SetRotate(Point3D(0,0,0));
	leftHand->SetRotate(Point3D(0,0,0));
	upperLegRight->SetRotate(Point3D(0,0,0));
	lowerLegRight->SetRotate(Point3D(0,0,0));
	rightHand->SetRotate(Point3D(0,0,0));
	upperLegLeft->SetRotate(Point3D(0,0,0));
	lowerLegLeft->SetRotate(Point3D(0,0,0));
	rightHand->SetRotate(Point3D(0,0,0));
	body->SetRotate(Point3D(0,0,0));

	//Mesh* mesh = new Mesh("Mario.txt");
	//mesh->Translate(Point3D(0,20,0));

	//AddChild(mesh);
}

Mario::~Mario()
{

}

void Mario::DrawObject()
{
}

void Mario::Jump()
{
	if(!IsDead())
	{
		if(IsGrounded())
		{
			fallSpeed += 1.5;
		}
		JumpAnimation();
	}
}


void Mario::RunAnimation()
{
	if(animation != MarioAnimations::Run)
	{
		body->SetAnimation(Animation());
		body->SetRotate(Point3D(0,0,0));

		Animation pelvisAnimation;
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,210,0),pelvis->GetTranslate()));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,170,0),pelvis->GetTranslate()));
		pelvis->SetAnimation(pelvisAnimation);

		Animation upperLegRightAnimation;
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(110,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-100,0,0),upperLegRight->GetTranslate()));
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
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-100,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(110,0,0),upperLegLeft->GetTranslate()));
		upperLegLeft->SetAnimation(upperLegLeftAnimation);

		Animation lowerLegLeftAnimation;
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-120,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeft->SetAnimation(lowerLegLeftAnimation);
		
		Animation leftFootAnimation;
		leftFootAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),leftFoot->GetTranslate()));
		leftFootAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),leftFoot->GetTranslate()));
		leftFoot->SetAnimation(leftFootAnimation);

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(-10,0,60), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(100,0,60), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		
		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(30,0,0),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);

		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(100,0,-60), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(-10,0,-60), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);

		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(30,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);

		animation = MarioAnimations::Run;
	}
}

void Mario::JumpAnimation()
{
	if(animation != MarioAnimations::Jump)
	{
		/*Animation pelvisAnimation;
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,200,0),pelvis->GetTranslate()));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,160,0),pelvis->GetTranslate()));
		pelvis->SetAnimation(pelvisAnimation);*/

		body->SetAnimation(Animation());
		body->SetRotate(Point3D(0,0,0));
		pelvis->SetAnimation(Animation());
		pelvis->SetRotate(Point3D(0,190,0));
		
		Animation upperLegRightAnimation;
		upperLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(50,0,0),upperLegRight->GetTranslate()));
		upperLegRight->SetAnimation(upperLegRightAnimation);

		Animation lowerLegRightAnimation;
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(-100,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),lowerLegRight->GetTranslate()));
		lowerLegRight->SetAnimation(lowerLegRightAnimation);

		Animation rightFootAnimation;
		rightFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(-100,0,0),rightFoot->GetTranslate()));
		rightFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),rightFoot->GetTranslate()));
		rightFoot->SetAnimation(rightFootAnimation);

		Animation upperLegLeftAnimation;
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(50,0,0),upperLegLeft->GetTranslate()));
		upperLegLeft->SetAnimation(upperLegLeftAnimation);

		Animation lowerLegLeftAnimation;
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(-100,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeft->SetAnimation(lowerLegLeftAnimation);
		
		Animation leftFootAnimation;
		leftFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(-100,0,0),leftFoot->GetTranslate()));
		leftFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),leftFoot->GetTranslate()));
		leftFoot->SetAnimation(leftFootAnimation);

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,-50), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,-50),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);


		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,50), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);
		
		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,50),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);

		animation = MarioAnimations::Jump;
	}
}

void Mario::HitAnimation()
{
	if(animation != MarioAnimations::Hit)
	{
		Animation bodyAnimation;
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-30,0,0),body->GetTranslate()));
	    bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),body->GetTranslate()));
		body->SetAnimation(bodyAnimation);

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(-10,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(-20,0,0), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);


		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(-10,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(-20,0,0), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);
		
		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);


		Animation upperLegRightAnimation;
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(200,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(230,0,0),upperLegRight->GetTranslate()));
		upperLegRight->SetAnimation(upperLegRightAnimation);

		Animation lowerLegRightAnimation;
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegRight->GetTranslate()));
		lowerLegRight->SetAnimation(lowerLegRightAnimation);

		Animation upperLegLeftAnimation;
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(200,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(230,0,0),upperLegLeft->GetTranslate()));
		upperLegLeft->SetAnimation(upperLegLeftAnimation);

		Animation lowerLegLeftAnimation;
	    lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeft->SetAnimation(lowerLegLeftAnimation);
		
	
	animation=MarioAnimations::Hit;
	}
}
void Mario::DeadAnimation()
{
	if(animation != MarioAnimations::Dead)
	{
		Animation pelvisAnimation;
		pelvisAnimation.AddAnimationStep(AnimationStep(0.01,Point3D(0,180,0),pelvis->GetTranslate()));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,180,0),pelvis->GetTranslate()));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-90,180,0),Point3D(pelvis->GetTranslate().x,pelvis->GetTranslate().y+5,pelvis->GetTranslate().z)));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-100,180,0),pelvis->GetTranslate()));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-80,180,0),Point3D(pelvis->GetTranslate().x,1,pelvis->GetTranslate().z)));
		pelvisAnimation.AddAnimationStep(AnimationStep(3,Point3D(-90,180,0),Point3D(pelvis->GetTranslate().x,1,pelvis->GetTranslate().z)));
		pelvis->SetAnimation(pelvisAnimation);

     /*   Animation bodyAnimation;
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-30,0,0),body->GetTranslate()));
	    bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-40,0,0),body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0), body->GetTranslate()));
        bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-80,0,0), body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-90,0,0),body->GetTranslate()));
		body->SetAnimation(bodyAnimation);*/

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(10,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(20,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(30,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,0), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(10,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmRight->GetTranslate()));
	    lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(30,0,0),lowerArmRight->GetTranslate()));
	    lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmRight->GetTranslate()));
	    lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);

        Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(10,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(20,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(30,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);
		
		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(10,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(30,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);


		Animation upperLegRightAnimation;
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(40,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(90,0,0), upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(60,0,0), upperLegRight->GetTranslate()));
        upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(60,0,0), upperLegRight->GetTranslate()));
        upperLegRight->SetAnimation(upperLegRightAnimation);

		Animation lowerLegRightAnimation;
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-30,0,0), lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0), lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0), lowerLegRight->GetTranslate()));
		lowerLegRight->SetAnimation(lowerLegRightAnimation);

		Animation upperLegLeftAnimation;
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(200,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(100,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(90,0,0), upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(150,0,0), upperLegLeft->GetTranslate()));
        upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(190,0,0), upperLegLeft->GetTranslate()));
        upperLegLeft->SetAnimation(upperLegLeftAnimation);

		Animation lowerLegLeftAnimation;
	    lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-30,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));
	    lowerLegLeft->SetAnimation(lowerLegLeftAnimation);

		animation=MarioAnimations::Dead;
	}
}

void Mario::Update()
{
	PhysicsObject::Update();

	if(scene != NULL)
	{
		if(mesh == NULL)
		{
			mesh = new Skin("Mario.txt",true);

			vector<int> bindingHead;
			vector<int> bindingBody;

			ifstream f("MarioHeadBinds.txt");
			while(!f.eof())
			{
				int p;
				f>>p;
				bindingHead.push_back(p);
				bindingHead.push_back(p+136);
			}

			f.close();
			ifstream q("MarioBodyBinds.txt");
			while(!q.eof())
			{
				int p;
				q>>p;
				bindingBody.push_back(p);
				bindingBody.push_back(p+136);
			}
			q.close();

			vector<int> bindingUpperLegRight;
			vector<int> bindingLowerLegRight;
			vector<int> bindingRightFoot;

			vector<int> bindingUpperLegLeft;
			vector<int> bindingLowerLegLeft;
			vector<int> bindingLeftFoot;

			ifstream urlFile("UpperLegRight.txt");
			int p;
			while(!urlFile.eof())
			{				
				urlFile>>p;
				bindingUpperLegRight.push_back(p);
				bindingUpperLegLeft.push_back(p+136);
			}

			ifstream llrFile("LowerLegRight.txt");
			while(!llrFile.eof())
			{
				int p;
				llrFile>>p;
				bindingLowerLegRight.push_back(p);
				bindingLowerLegLeft.push_back(p+136);
			}

			ifstream rfFile("RightFoot.txt");
			while(!rfFile.eof())
			{
				int p;
				rfFile>>p;
				bindingRightFoot.push_back(p);
				bindingLeftFoot.push_back(p+136);
			}

			vector<int> bindingUpperArmRight;
			vector<int> bindingLowerArmRight;
			vector<int> bindingRightHand;

			vector<int> bindingUpperArmLeft;
			vector<int> bindingLowerArmLeft;
			vector<int> bindingLeftHand;

			ifstream ualFile("UpperArmRight.txt");
			while(!ualFile.eof())
			{				
				int p;
				ualFile>>p;
				bindingUpperArmRight.push_back(p);
				bindingUpperArmLeft.push_back(p+136);
			}

			ifstream larFile("LowerArmRight.txt");
			while(!larFile.eof())
			{
				int p;
				larFile>>p;
				bindingLowerArmRight.push_back(p);
				bindingLowerArmLeft.push_back(p+136);
			}

			ifstream rhFile("RightHand.txt");
			while(!rhFile.eof())
			{
				int p;
				rhFile>>p;
				bindingRightHand.push_back(p);
				bindingLeftHand.push_back(p+136);
			}

			mesh->AddBind(body,bindingBody);
			mesh->AddBind(head,bindingHead);
			mesh->AddBind(upperLegRight,bindingUpperLegRight);
			mesh->AddBind(lowerLegRight,bindingLowerLegRight);
			mesh->AddBind(rightFoot,bindingRightFoot);
			mesh->AddBind(upperLegLeft,bindingUpperLegLeft);
			mesh->AddBind(lowerLegLeft,bindingLowerLegLeft);
			mesh->AddBind(leftFoot,bindingLeftFoot);
			mesh->AddBind(upperArmRight,bindingUpperArmRight);
			mesh->AddBind(lowerArmRight,bindingLowerArmRight);
			mesh->AddBind(rightHand,bindingRightHand);
			mesh->AddBind(upperArmLeft,bindingUpperArmLeft);
			mesh->AddBind(lowerArmLeft,bindingLowerArmLeft);
			mesh->AddBind(leftHand,bindingLeftHand);
			pelvis->Translate(Point3D(0,8,0));
			
			scene->AddObject(mesh);
			Translate(Point3D(0.1,0.0,0.0));
			RunAnimation();
		}
		else
		{
			//mesh->SetRotate(rotate);
		}

		if(dustTrail == NULL)
		{
			//dustTrail = new Particles(BackDirection, 
			//	Origin, 
			//	DustGenerator, 
			//	Point3D(1,1,1),
			//	Point3D(0,0,0),
			//	RandomDirection, 
			//	NULL,
			//	VarySpeed,
			//	21);

			//scene->AddObject(dustTrail);
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

	if(deadMario == false)
	{
		Translate(GetForward()*forwardSpeed);

		if(Input::GetLeft())
			//Rotate(Point3D(0,-4,0));
			this->MoveLeft();

		if(Input::GetRight())
			//Rotate(Point3D(0,4,0));
			this->MoveRight();

		if(translate.y == 0)
		{
			if(animation == MarioAnimations::Jump)
				RunAnimation();
		}
		else
		{
			if(animation == MarioAnimations::Run)
				JumpAnimation();
		}

		if(forwardSpeed < -0.5)
		{
			HitAnimation();
		}
		else
		{
			if(animation == MarioAnimations::Hit)
				RunAnimation();
		}
	}

	else if(deadMario == true)
	{
		dying += 0.05;
	}

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

	scene->DeleteUntil(this);

	if(this->GetIndex() == 3)
		road->GenerateRoad();
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
				goomba->SetDamage();
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

void Mario::SetDead()
{
	deadMario = !deadMario;
	DeadAnimation();
}

bool Mario::IsDead()
{
	if(dying > 4.0)
		return true;

	return false;
}