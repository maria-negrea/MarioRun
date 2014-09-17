#include "AnimationStep.h"

AnimationStep::AnimationStep(double time,Point3D rotation,Point3D translate)
	:time(time),rotation(rotation),translate(translate)
{

}

AnimationStep::~AnimationStep(void)
{
}

Point3D AnimationStep::GetRotation()
{
	return rotation;
}

Point3D AnimationStep::GetTranslate()
{
	return translate;
}

double AnimationStep::GetTime()
{
	return time;
}