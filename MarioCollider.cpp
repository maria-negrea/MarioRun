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

	if(newItem != NULL && newItem->Function(mario))
	{}

	else
	{
		if(mario->GetInvulnerable() == false && mario->GetBleep() == false)
		{
			bool isBig = mario->IsBig();
			Collider::Hit(collision);
			mario->Hit(collision);

			Enemy* enemy = dynamic_cast<Enemy*>(collision.GetHitObject());

			if(enemy != NULL && isBig == false && enemy->IsDamaged() == false)
					mario->SetDead();
		}
	}
}