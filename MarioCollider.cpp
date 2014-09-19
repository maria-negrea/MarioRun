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
	WorldObject* obj = collision.GetHitObject();
	Item *newItem = dynamic_cast<Item*>(collision.GetHitObject());

	if(newItem != NULL)
	{
		newItem->Function(mario);
	}

	else
	{
		Collider::Hit(collision);
		mario->Hit(collision);
	}
}