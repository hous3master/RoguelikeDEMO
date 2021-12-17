#pragma once
#include "Player.h"
#include "Ghost.h"
#include "Fireball.h"
class Game
{
private:
	Player* objPlayer;
	vector<Entity*> arrEntity;
	time_t timer;
	int points;
public:
	Game();
	~Game();
	void Insert_Ghosts();
	void Draw_Player(Graphics^ g, Bitmap^ bmp);
	void Draw_Vector(Graphics^ g, Bitmap^ bmpGhost, Bitmap^ bmpFireball);
	void Shoot();
	void Colision();
	bool End_Game();
	void new_orientation(direction new_data);
	System::String^ return_text_lifes();
	System::String^ return_text_points();
};

