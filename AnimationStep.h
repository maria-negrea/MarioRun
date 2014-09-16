#pragma once
#include "WorldObject.h"

class AnimationStep
{
	double time;
	Point3D rotation;
	Point3D translate;
public:
	AnimationStep(double time,Point3D rotation,Point3D translate = 0.0);
	~AnimationStep();

	Point3D GetTranslate();
	Point3D GetRotation();
	double GetTime();
};
