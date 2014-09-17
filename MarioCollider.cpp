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
	mario->Translate(-collision.GetDirection());
	mario->Hit(collision);
}