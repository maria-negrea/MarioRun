#pragma once
#include "WorldObject.h"

class AnimationStep
{
	double time;
	Point3D rotation;
public:
	AnimationStep(double time,Point3D rotation);
	~AnimationStep();

	Point3D GetRotation();
	double GetTime();
};
