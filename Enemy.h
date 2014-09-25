#pragma once

class Enemy
{
protected:
	bool isDamaged;
public:
	Enemy(void);
	~Enemy(void);
	virtual void SetDamage() = 0;
	virtual bool IsDamaged() = 0;
};
