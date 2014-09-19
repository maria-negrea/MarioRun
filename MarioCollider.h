#pragma once
#include "Collider.h"
#include "Mario.h"
#include "Coin.h"
#include "FireBall.h"

class MarioCollider : public Collider
{
	Mario* mario;
public:
	void Hit(Collision collision);
	MarioCollider(Mario* mario);
	~MarioCollider(void);
};