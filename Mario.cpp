#include "Mario.h"
#include "MarioCollider.h"
#include "Goomba.h"
#include "Box.h"
#include "Mesh.h"

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

Mario::Mario(Environmental* enviroment):PhysicsObject(0.0),OnRoadObject(true)
{
	this->environment=enviroment;
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
	drown = false;
	startGame = false;

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
	upperLegLeft->Rotate(Point3D(180,0,0));
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

	body->AddChild(upperArmRight);
	upperArmRight->AddChild(lowerArmRight);
	lowerArmRight->AddChild(rightHand);

	body->AddChild(upperArmLeft);
	upperArmLeft->AddChild(lowerArmLeft);
	lowerArmLeft->AddChild(leftHand);

	mesh = new Mesh("Mario.txt");
	mesh->Scale(Point3D(-0.94,-0.94,-0.94));
	mesh->Translate(Point3D(0,10,0));
	AddChild(mesh);

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
		neck->SetAnimation(Animation());

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

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(80,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(260,0,0), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		
		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(150,0,0),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);

		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(260,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(80,0,0), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);

		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(150,0,0),lowerArmLeft->GetTranslate()));
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
	  pelvis->SetAnimation(Animation());
	  
	  Animation upperLegRightAnimation;
	  upperLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(-85,0,0),upperLegRight->GetTranslate()));
	  upperLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(-120,0,0),upperLegRight->GetTranslate()));
	  upperLegRight->SetAnimation(upperLegRightAnimation);

	  //Animation lowerLegRightAnimation;
	  //lowerLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(10,0,0),lowerLegRight->GetTranslate()));
	  //lowerLegRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(20,0,0),lowerLegRight->GetTranslate()));
	  //lowerLegRight->SetAnimation(lowerLegRightAnimation);

	  Animation rightFootAnimation;
	  rightFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(50,0,0),rightFoot->GetTranslate()));
	  rightFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),rightFoot->GetTranslate()));
	  rightFoot->SetAnimation(rightFootAnimation);

	  Animation upperLegLeftAnimation;
	  upperLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(-85,0,0),upperLegLeft->GetTranslate()));
	  upperLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(-120,0,0),upperLegLeft->GetTranslate()));
	  upperLegLeft->SetAnimation(upperLegLeftAnimation);

	 /* Animation lowerLegLeftAnimation;
	  lowerLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(10,0,0),lowerLegLeft->GetTranslate()));
	  lowerLegLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(20,0,0),lowerLegLeft->GetTranslate()));
	  lowerLegLeft->SetAnimation(lowerLegLeftAnimation);*/
	  
	  Animation leftFootAnimation;
	  leftFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(50,0,0),leftFoot->GetTranslate()));
	  leftFootAnimation.AddAnimationStep(AnimationStep(2,Point3D(-50,0,0),leftFoot->GetTranslate()));
	  leftFoot->SetAnimation(leftFootAnimation);

	  Animation upperArmRightAnimation;
	  upperArmRightAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,-90), upperArmRight->GetTranslate()));
	  upperArmRightAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,-180), upperArmRight->GetTranslate()));
	  upperArmRight->SetAnimation(upperArmRightAnimation);

	  Animation lowerArmRightAnimation;
	  lowerArmRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,150),lowerArmRight->GetTranslate()));
	  lowerArmRightAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,0),lowerArmRight->GetTranslate()));
	  lowerArmRight->SetAnimation(lowerArmRightAnimation);


	  Animation upperArmLeftAnimation;
	  upperArmLeftAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,90), upperArmLeft->GetTranslate()));
	  upperArmLeftAnimation.AddAnimationStep(AnimationStep(2, Point3D(0,0,180), upperArmLeft->GetTranslate()));
	  upperArmLeft->SetAnimation(upperArmLeftAnimation);
	  
	  Animation lowerArmLeftAnimation;
	  lowerArmLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,-150),lowerArmLeft->GetTranslate()));
	  lowerArmLeftAnimation.AddAnimationStep(AnimationStep(2,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
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
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(30,0,0),body->GetTranslate()));
	    bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),body->GetTranslate()));
		body->SetAnimation(bodyAnimation);

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(10,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(20,0,0), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(10,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);


		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(10,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(20,0,0), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);
		
		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(10,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);


		Animation upperLegRightAnimation;
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(160,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(140,0,0),upperLegRight->GetTranslate()));
		upperLegRight->SetAnimation(upperLegRightAnimation);

		Animation lowerLegRightAnimation;
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegRight->GetTranslate()));
		lowerLegRight->SetAnimation(lowerLegRightAnimation);

		Animation upperLegLeftAnimation;
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(160,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(140,0,0),upperLegLeft->GetTranslate()));
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
	{neck->SetAnimation(Animation());
	 pelvis->SetAnimation(Animation());


		Animation pelvisAnimation;
		pelvisAnimation.AddAnimationStep(AnimationStep(0.01,Point3D(0,180,0),pelvis->GetTranslate()));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,180,0),pelvis->GetTranslate()));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-90,180,-80),Point3D(pelvis->GetTranslate().x,pelvis->GetTranslate().y+5,pelvis->GetTranslate().z)));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-100,180,-100),Point3D(pelvis->GetTranslate().x,pelvis->GetTranslate().y+5,pelvis->GetTranslate().z)));
		pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-80,180,-120),Point3D(pelvis->GetTranslate().x,1,pelvis->GetTranslate().z)));
		pelvisAnimation.AddAnimationStep(AnimationStep(3,Point3D(-90,180,-160),Point3D(pelvis->GetTranslate().x,1,pelvis->GetTranslate().z)));
		pelvis->SetAnimation(pelvisAnimation);

     /*   Animation bodyAnimation;
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-30,0,0),body->GetTranslate()));
	    bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-40,0,0),body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0), body->GetTranslate()));
        bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-80,0,0), body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-90,0,0),body->GetTranslate()));
		body->SetAnimation(bodyAnimation);*/

		Animation neckAnimation;
		neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0), neck->GetTranslate()));
        neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0), neck->GetTranslate()));
        neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,-90,0), neck->GetTranslate()));
        neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,-90,0), neck->GetTranslate()));
        neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,-90,0), neck->GetTranslate()));
        neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,-90,0), neck->GetTranslate()));
        neck->SetAnimation(neckAnimation);


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
void Mario::WaveAnimation()
{	
	if(animation != MarioAnimations::Wave)
	{   
		upperLegLeft->SetAnimation(Animation());
		lowerLegLeft->SetAnimation(Animation());
		leftFoot->SetAnimation(Animation());
		upperLegRight->SetAnimation(Animation());
		lowerLegRight->SetAnimation(Animation());
		rightFoot->SetAnimation(Animation());
		pelvis->SetAnimation(Animation());

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,190), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,190), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		
		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,10),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,10),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);

		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,120), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,80), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);

		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,-30),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,-60),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);

		Animation leftHandAnimation;
		leftHandAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,-10), leftHand->GetTranslate()));
        leftHandAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,-15), leftHand->GetTranslate()));
        leftHand->SetAnimation(leftHandAnimation);


		animation = MarioAnimations::Wave;
	}

}
void Mario::SpecialRunAnimation()
{
if(animation != MarioAnimations::SpecialRun)
	{
		body->SetAnimation(Animation());

        Animation neckAnimation;
		neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,200,0),neck->GetTranslate()));
		neckAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,90,0), neck->GetTranslate()));
		neck->SetAnimation(neckAnimation);

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


		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,80), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,260), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		
		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-150,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);

		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,260), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,80), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);

		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-150,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);

		animation = MarioAnimations::SpecialRun;
	}
}

void Mario::DrownAnimation()
{
	if(animation != MarioAnimations::Drown)
	{ 
	  body->SetAnimation(Animation());
	  neck->SetAnimation(Animation());

	  Animation pelvisAnimation;
	  pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,180,0),Point3D(pelvis->GetTranslate().x,-2,pelvis->GetTranslate().z)));
	  pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,180,0),Point3D(pelvis->GetTranslate().x,-3,pelvis->GetTranslate().z)));
	  /*pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-90,180,0),Point3D(pelvis->GetTranslate().x,pelvis->GetTranslate().y+5,pelvis->GetTranslate().z)));
	  pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-100,180,0),pelvis->GetTranslate()));
	  pelvisAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-80,180,0),Point3D(pelvis->GetTranslate().x,1,pelvis->GetTranslate().z)));
	  pelvisAnimation.AddAnimationStep(AnimationStep(3,Point3D(-90,180,0),Point3D(pelvis->GetTranslate().x,1,pelvis->GetTranslate().z)));
	  */pelvis->SetAnimation(pelvisAnimation);

	    Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,10), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,30), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		
		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,-20),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,-80),lowerArmRight->GetTranslate()));
		lowerArmRight->SetAnimation(lowerArmRightAnimation);

		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,-10), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,0,-30), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);

		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,20),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,80),lowerArmLeft->GetTranslate()));
		lowerArmLeft->SetAnimation(lowerArmLeftAnimation);

		Animation neckAnimation;
		neckAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,150,0),neck->GetTranslate()));
		neckAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(0,90,0), neck->GetTranslate()));
		neck->SetAnimation(neckAnimation);


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
		
animation=MarioAnimations::Drown;
}

}
void Mario::SlideAnimation()
{
	if(animation != MarioAnimations::Slide)
	{
		Animation bodyAnimation;
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(30,0,0),body->GetTranslate()));
	    bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),body->GetTranslate()));
		bodyAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(70,0,0),body->GetTranslate()));
		body->SetAnimation(bodyAnimation);

		Animation upperArmRightAnimation;
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(10,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(20,0,0), upperArmRight->GetTranslate()));
		upperArmRightAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(30,0,0), upperArmRight->GetTranslate()));
		upperArmRight->SetAnimation(upperArmRightAnimation);

		Animation lowerArmRightAnimation;
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(10,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmRight->GetTranslate()));
		lowerArmRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(10,0,0),lowerArmRight->GetTranslate()));
        lowerArmRight->SetAnimation(lowerArmRightAnimation);


		Animation upperArmLeftAnimation;
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(10,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(20,0,0), upperArmLeft->GetTranslate()));
		upperArmLeftAnimation.AddAnimationStep(AnimationStep(1.5, Point3D(30,0,0), upperArmLeft->GetTranslate()));
		upperArmLeft->SetAnimation(upperArmLeftAnimation);
		
		Animation lowerArmLeftAnimation;
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(10,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(20,0,0),lowerArmLeft->GetTranslate()));
		lowerArmLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(15,0,0),lowerArmLeft->GetTranslate()));
	    lowerArmLeft->SetAnimation(lowerArmLeftAnimation);


		Animation upperLegRightAnimation;
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(160,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(140,0,0),upperLegRight->GetTranslate()));
		upperLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(130,0,0),upperLegRight->GetTranslate()));
		upperLegRight->SetAnimation(upperLegRightAnimation);

		Animation lowerLegRightAnimation;
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegRight->GetTranslate()));
		lowerLegRightAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-25,0,0),lowerLegRight->GetTranslate()));
	    lowerLegRight->SetAnimation(lowerLegRightAnimation);

		Animation upperLegLeftAnimation;
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(180,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(160,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(110,0,0),upperLegLeft->GetTranslate()));
		upperLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(100,0,0),upperLegLeft->GetTranslate()));
		upperLegLeft->SetAnimation(upperLegLeftAnimation);

		Animation lowerLegLeftAnimation;
	    lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-10,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-20,0,0),lowerLegLeft->GetTranslate()));
		lowerLegLeftAnimation.AddAnimationStep(AnimationStep(1.5,Point3D(-30,0,0),lowerLegLeft->GetTranslate()));
	    lowerLegLeft->SetAnimation(lowerLegLeftAnimation);
		
	    animation=MarioAnimations::Slide;
	} 
}

void Mario::Update()
{
	PhysicsObject::Update();

	/*if(scene != NULL)
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
				21);

			scene->AddObject(dustTrail);
		}
	}*/

	/*if(dustTrail != NULL)
	{
		dustTrail->SetTranslate(translate);
		dustTrail->SetRotate(rotate);
	}*/

	if(startGame == false)
	{
		WaveAnimation();
		return;
	}

	if(!deadMario && !invulnerable)
		RunAnimation();

	forwardSpeed += acceleration;
	if(forwardSpeed > maxSpeed)
		forwardSpeed = maxSpeed;

	if(deadMario == false)
	{
		Translate(GetForward()*forwardSpeed);

		if(Input::GetLeft())
		//	Rotate(Point3D(0,4,0));
			this->MoveLeft();

		if(Input::GetRight())
		//	Rotate(Point3D(0,4,0));
			this->MoveRight();

		if(translate.y == 0)
		{
			if(animation == MarioAnimations::Jump)
				RunAnimation();

			if(animation == MarioAnimations::Run && invulnerable == true)
				SpecialRunAnimation();

			if(animation == MarioAnimations::SpecialRun && invulnerable == false)
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

	else
		dying += 0.05;

	if(bleep == true && drown == false)
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
	{
		road->GenerateRoad();
		environment->GenerateEnvironment();
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
	deadMario = true;
	bleep = false;
	if(drown)
		DrownAnimation();
	else
		DeadAnimation();
}

bool Mario::IsDead()
{
	if(dying > 3)
		return true;

	return false;
}

void Mario::SetDrown()
{
	drown = true;
}

void Mario::StartGame()
{
	startGame = true;
}

bool Mario::GameStatus()
{
	return startGame;
}

bool Mario::IsDying()
{
	return deadMario;
}