#pragma once
#include "Head.h"
#include "Torso.h"
#include "Foot.h"
#include "Enemy.h"

class Goomba: public WorldObject, public Updatable, public Enemy
{
protected:
	WorldObject* target;
	GLfloat speed;

	double deathTime;
	bool dead;
public:
	Goomba(void);
	void DrawObject();
	void Update();
	void SetTarget(WorldObject* target);
	~Goomba(void);

	void Damage();
	bool IsDamaged();
	void SetDamage();
};
