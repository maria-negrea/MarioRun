#pragma once
#include "WorldObject.h"
#include "Updatable.h"
#include "AnimationStep.h"

class AnimatedWorldObject : public WorldObject, public Updatable
{
	vector<AnimationStep> animations;
	double fullTime;
	int stepIndex;
public:
	AnimatedWorldObject();
	~AnimatedWorldObject();
	void Update();

	void AddAnimationStep(AnimationStep step);
};
