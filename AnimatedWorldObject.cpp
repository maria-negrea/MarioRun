#include "AnimatedWorldObject.h"

AnimatedWorldObject::AnimatedWorldObject()
	:WorldObject()
{
}

AnimatedWorldObject::~AnimatedWorldObject()
{
}

void AnimatedWorldObject::Update()
{
	currentAnimation.Update(this);
}

void AnimatedWorldObject::SetAnimation(Animation animation)
{
	this->currentAnimation = animation;
}