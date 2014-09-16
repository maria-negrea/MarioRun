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
	translate.z = (follow->GetTranslate()-follow->GetForward()*30).z;
}