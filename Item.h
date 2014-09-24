#pragma once

class Mario;

class Item
{
public:
	Item(void);
	~Item(void);
	virtual bool Function(Mario *mario) = 0;
};

#include "Mario.h"
