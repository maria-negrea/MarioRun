#include "Goomba.h"
#include "Pivot.h"
#include "Input.h"

Goomba::Goomba(void)
{
	Head *head = new Head();
	Torso *torso = new Torso();
	Foot *leftFoot = new Foot();
	Foot *rightFoot = new Foot();
	speed=1.1;

	width=head->GetBigRadius()*2;
	length=head->GetSmallRadius()*2;
	height=5.5;

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

	head->AddAnimationStep(AnimationStep(3, Point3D(0, 10, 0), Point3D(0.0, 1.5, 0.0)));
	head->AddAnimationStep(AnimationStep(3, Point3D(0, -10, 0), Point3D(0.0, 1.5, 0.0)));
	
	pivotLeftFoot->AddAnimationStep(AnimationStep(0.5, Point3D(-25.0, 0, 0), Point3D(-0.25,0.5,-0.1)));
	pivotLeftFoot->AddAnimationStep(AnimationStep(0.5, Point3D(25.0, 0, 0), Point3D(-0.25,0.5,-0.1)));

	pivotRightFoot->AddAnimationStep(AnimationStep(0.5, Point3D(25.0, 0, 0), Point3D(0.25, 0.5, -0.1)));
	pivotRightFoot->AddAnimationStep(AnimationStep(0.5, Point3D(-25.0, 0, 0), Point3D(0.25, 0.5, -0.1)));

	target = NULL;
}

void Goomba:: DrawObject()
{
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
	if(target != NULL)
	{
		Translate(GetForward()*speed);
		
		Point3D point = target->GetTranslate()-GetTranslate();
		point.y = 0;

		GLfloat angleToTarget = AngleBetween(point);
		Rotate(Point3D(0.0,angleToTarget, 0.0));
	}

	if(Input::GetLeft())
		Translate(Point3D(-10,0,0));
}

Goomba::~Goomba(void)
{
}
