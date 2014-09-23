#include "Goomba.h"
#include "Pivot.h"
#include "Input.h"

Goomba::Goomba(void)
{
	Head *head = new Head();
	Torso *torso = new Torso();
	speed=1.05;

	AddCollider();
	hardCollider = true;
	Foot *leftFoot = new Foot(6);
	Foot *rightFoot = new Foot(6);

	width=head->GetBigRadius()*2;
	length=head->GetSmallRadius()*2;
	height=5.5;
	width = head->GetBigRadius()*2;
	length = head->GetSmallRadius()*2;

	Pivot *pivotLeftFoot = new Pivot();
	pivotLeftFoot->AddChild(leftFoot);
	leftFoot->Translate(Point3D(-0.25,-0.5,0.2));
	leftFoot->Rotate(Point3D(0,110,0));

	Pivot *pivotRightFoot = new Pivot();
	pivotRightFoot->AddChild(rightFoot);
	rightFoot->Translate(Point3D(0.25,-0.5,0.2));
	rightFoot->Rotate(Point3D(0,70,0));


	AddChild(head);
	AddChild(torso);
	AddChild(pivotLeftFoot);
	AddChild(pivotRightFoot);
	torso->Translate(Point3D(0.0, 0.5, 0.0));

	Animation headAnimation;
	headAnimation.AddAnimationStep(AnimationStep(3, Point3D(0, 10, 0), Point3D(0.0, 1.5, 0.0)));
	headAnimation.AddAnimationStep(AnimationStep(3, Point3D(0, -10, 0), Point3D(0.0, 1.5, 0.0)));
	head->SetAnimation(headAnimation);


	Animation leftFootAnimation;
	leftFootAnimation.AddAnimationStep(AnimationStep(0.5, Point3D(-25.0, 0, 0), Point3D(-0.25,0.5,-0.1)));
	leftFootAnimation.AddAnimationStep(AnimationStep(0.5, Point3D(25.0, 0, 0), Point3D(-0.25,0.5,-0.1)));	
	pivotLeftFoot->SetAnimation(leftFootAnimation);

	Animation rightFootAnimation;
	rightFootAnimation.AddAnimationStep(AnimationStep(0.5, Point3D(25.0, 0, 0), Point3D(0.25, 0.5, -0.1)));
	rightFootAnimation.AddAnimationStep(AnimationStep(0.5, Point3D(-25.0, 0, 0), Point3D(0.25, 0.5, -0.1)));
	pivotRightFoot->SetAnimation(rightFootAnimation);

	target = NULL;
	dead = false;
}

void Goomba:: DrawObject()
{
}

void Goomba::Damage()
{
	dead = true;
	deathTime = 3.0;
	RemoveCollider();
}

void Goomba:: SetTarget(WorldObject* target)
{
	if(target!=NULL)
	{
		this->target=target;
	}
}

#include <iostream>
void Goomba::Update()
{
	if(dead)
	{
		deathTime -= 0.1;
		scale.y = scale.y*0.8;
		if(deathTime < 0)
		{
			scene->RemoveObject(this);
		}
	}
	else
	{
		if(target != NULL)
		{
			Translate(GetForward()*speed);
			
			Point3D point = target->GetTranslate()-GetTranslate();
			point.y = 0;

			GLfloat angleToTarget = AngleBetween(point);
			Rotate(Point3D(0.0,angleToTarget, 0.0));
		}
	}
}

Goomba::~Goomba(void)
{
}
