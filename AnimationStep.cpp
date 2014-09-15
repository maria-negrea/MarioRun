#include "AnimationStep.h"

AnimationStep::AnimationStep(double time,Point3D rotation)
	:time(time),rotation(rotation)
{

}

AnimationStep::~AnimationStep(void)
{
}

Point3D AnimationStep::GetRotation()
{
	return rotation;
}

double AnimationStep::GetTime()
{
	return time;
}
