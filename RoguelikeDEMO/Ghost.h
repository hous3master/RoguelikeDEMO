#pragma once
#include "Entity.h"
class Ghost: public Entity
{
public:
	Ghost();
	Ghost(int px, int py, int pw, int ph);
	~Ghost();
};

