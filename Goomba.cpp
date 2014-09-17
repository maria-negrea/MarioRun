#include "Goomba.h"

Goomba::Goomba(void)
{
	head=new Head();
	torso=new Torso();
	leftFoot=new Foot();
	rightFoot=new Foot();
	leftFoot->Translate(Point3D(-0.5, 0.0, 0.0));
	leftFoot->Rotate(Point3D(0.0, 80.0, 335.0));
	rightFoot->Translate(Point3D(0.5, 0.0, 0.0));
	rightFoot->Rotate(Point3D(0.0, 110.0, 335.0));
	torso->Translate(Point3D(0.0, 0.5, 0.0));
	head->Translate(Point3D(0.0, 1.5, 0.0));
}

void Goomba:: DrawObject()
{
	leftFoot->Draw();
	rightFoot->Draw();
	torso->Draw();
	head->Draw();

}

void Goomba::Update()
{
}

Goomba::~Goomba(void)
{
}
