#include "MarioCollider.h"

MarioCollider::MarioCollider(Mario* mario)
	:mario(mario)
{
}

MarioCollider::~MarioCollider(void)
{
}

void MarioCollider::Hit(Collision collision)
{
	mario->Hit(collision);
}