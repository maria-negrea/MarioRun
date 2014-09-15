#include "AnimatedWorldObject.h"

AnimatedWorldObject::AnimatedWorldObject()
{
	fullTime = 0;
	stepIndex = 0;
}

AnimatedWorldObject::~AnimatedWorldObject()
{
}

void AnimatedWorldObject::Update()
{
	fullTime += 0.1;

	if(animations.size() > 0)
	{
		if(fullTime > animations[stepIndex].GetTime())
		{
			fullTime -= animations[stepIndex].GetTime();
			if(stepIndex == animations.size()-1)
			{
				stepIndex = 0;
			}
			else
			{
				++stepIndex;
			}
		}
		
		int lastIndex = stepIndex - 1;
		if(lastIndex < 0)
			lastIndex = animations.size()-1;

		Point3D extra = animations[stepIndex].GetRotation()-animations[lastIndex].GetRotation();

		extra = extra.Normalize()*fullTime*extra.Magnitude()/animations[stepIndex].GetTime();

		rotate = extra+animations[lastIndex].GetRotation();
	}
}

void AnimatedWorldObject::AddAnimationStep(AnimationStep step)
{
	animations.push_back(step);
}