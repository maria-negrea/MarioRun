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
	idealPosition = follow->GetTranslate()-follow->GetForward()*36+Point3D(0,15,0);
	idealRotation = follow->GetRotate().y;

	translate = idealPosition;
	rotate.y = idealRotation;
}