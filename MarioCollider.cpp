#include "MarioCollider.h"

MarioCollider::MarioCollider(Mario* mario)
	:mario(mario),Collider(mario)
{
}

MarioCollider::~MarioCollider(void)
{
}

void MarioCollider::Hit(Collision collision)
{
	Collider::Hit(collision);
	mario->Hit(collision);
}