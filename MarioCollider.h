#pragma once

#include "Collider.h"
#include "Mario.h"
#include "Item.h"
#include "Enemy.h"

class MarioCollider : public Collider
{
	Mario* mario;
public:
	void Hit(Collision collision);
	MarioCollider(Mario* mario);
	~MarioCollider(void);
};