#pragma once
#include "WorldObject.h"
#include "Updatable.h"
#include "AnimationStep.h"
#include "Animation.h"

class AnimatedWorldObject : public WorldObject, public Updatable
{
	Animation currentAnimation;
public:
	AnimatedWorldObject();
	~AnimatedWorldObject();

	void Update();
	void SetAnimation(Animation animation);
};
