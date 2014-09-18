#pragma once

#include "Mario.h"

class Item
{
public:
	Item(void);
	~Item(void);
	virtual void Function(Mario *mario) = 0;
};
