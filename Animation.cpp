#include "Animation.h"

Animation::Animation()
{
	fullTime = 0;
	stepIndex = 0;
}

Animation::~Animation(void)
{
}

void Animation::Update(AnimatedWorldObject* object)
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
		object->SetRotate(extra+animations[lastIndex].GetRotation());

		extra = animations[stepIndex].GetTranslate()-animations[lastIndex].GetTranslate();
		extra = extra.Normalize()*fullTime*extra.Magnitude()/animations[stepIndex].GetTime();	
		object->SetTranslate(extra+animations[lastIndex].GetTranslate());
	}
}

void Animation::AddAnimationStep(AnimationStep step)
{
	animations.push_back(step);
}