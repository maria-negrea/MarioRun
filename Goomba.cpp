#include "Goomba.h"
#include "Pivot.h"

Goomba::Goomba(void)
{
	Head *head = new Head();
	Torso *torso = new Torso();
	Foot *leftFoot = new Foot();
	Foot *rightFoot = new Foot();

	Pivot *pivotLeftFoot = new Pivot();
	pivotLeftFoot->AddChild(leftFoot);
	leftFoot->Translate(Point3D(-0.25,-0.5,0.2));
	leftFoot->Rotate(Point3D(0,110,0));

	Pivot *pivotRightFoot = new Pivot();
	pivotRightFoot->AddChild(rightFoot);
	rightFoot->Translate(Point3D(0.25,-0.5,0.2));
	rightFoot->Rotate(Point3D(0,70,0));


	children.push_back(head);
	children.push_back(torso);
	children.push_back(pivotLeftFoot);
	children.push_back(pivotRightFoot);
	torso->Translate(Point3D(0.0, 0.5, 0.0));

	head->AddAnimationStep(AnimationStep(3, Point3D(0, 10, 0), Point3D(0.0, 1.5, 0.0)));
	head->AddAnimationStep(AnimationStep(3, Point3D(0, -10, 0), Point3D(0.0, 1.5, 0.0)));
	
	pivotLeftFoot->AddAnimationStep(AnimationStep(2, Point3D(-25.0, 0, 0), Point3D(-0.25,0.5,-0.1)));
	pivotLeftFoot->AddAnimationStep(AnimationStep(2, Point3D(25.0, 0, 0), Point3D(-0.25,0.5,-0.1)));

	pivotRightFoot->AddAnimationStep(AnimationStep(2, Point3D(25.0, 0, 0), Point3D(0.25, 0.5, -0.1)));
	pivotRightFoot->AddAnimationStep(AnimationStep(2, Point3D(-25.0, 0, 0), Point3D(0.25, 0.5, -0.1)));

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
		Translate(GetForward()*0.1);
		GLfloat angleToTarget = AngleBetween(target);
		Rotate(Point3D(0.0,angleToTarget, 0.0));
	}
}

Goomba::~Goomba(void)
{
}
