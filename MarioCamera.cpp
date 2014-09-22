#include "MarioCamera.h"

MarioCamera::MarioCamera(WorldObject* follow)
{
	this->follow = follow;
}

MarioCamera::~MarioCamera(void)
{
}

void MarioCamera::Update()
{
	translate = (follow->GetTranslate()-follow->GetForward()*30)+Point3D(0,10,0);
	rotate.y = follow->GetRotate().y;
}