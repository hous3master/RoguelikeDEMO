#pragma once
#include "Entity.h"
class Player: public Entity
{
private:
	int lifes;
public:
	Player();
	Player(int px, int py, int pw, int ph);
	~Player();

	void new_lifes(int new_data);
	int return_lifes();
};

