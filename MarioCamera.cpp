#include "MarioCamera.h"

MarioCamera::MarioCamera(WorldObject* follow)
{
	this->follow = follow;

	idealRotation = rotate.y;
	idealPosition = translate;
}

MarioCamera::~MarioCamera(void)
{
}

void MarioCamera::Update()
{
	idealPosition = follow->GetTranslate()-follow->GetForward()*40+Point3D(0,10,0);
	idealRotation = follow->GetRotate().y;

	translate = idealPosition;
	rotate.y = idealRotation;
}