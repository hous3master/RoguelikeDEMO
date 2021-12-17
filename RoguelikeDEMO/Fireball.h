#pragma once
#include "Entity.h"
class Fireball : public Entity
{
public:
	Fireball();
	Fireball(int px, int py, int pw, int ph, direction player_orientation);
	~Fireball();
};

