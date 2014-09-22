#pragma once
#include "AnimationStep.h"

class AnimatedWorldObject;

class Animation
{
	vector<AnimationStep> animations;
	double fullTime;
	int stepIndex;
public:
	Animation();
	~Animation();

	void AddAnimationStep(AnimationStep step);
	void Update(AnimatedWorldObject* object);
};

#include "AnimatedWorldObject.h"
