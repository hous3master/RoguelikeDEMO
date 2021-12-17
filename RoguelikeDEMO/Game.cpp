#include "Game.h"
Game::Game() {
	objPlayer = new Player(200, 200, 1, 1);
	timer = time(0);
	points = 0;
}
Game::~Game(){}
void Game::Insert_Ghosts() {
	if (difftime(time(0), timer) > 0.5) {
		timer = time(0);
		System::Random^ rnd = gcnew System::Random();
		int ghost_x, ghost_y, ghost_dx, ghost_dy;
		int temp = rnd->Next(0, 4);
		if (temp == 0) { //Ghost appears left side
			ghost_x = 1;
			ghost_y = rnd->Next(1, 600);
			ghost_dx = rnd->Next(10, 30);
			ghost_dy = 0;
		}
		else if (temp == 1) { //Ghost appears right side
			ghost_x = 500;
			ghost_y = rnd->Next(1, 600);
			ghost_dx = -rnd->Next(10, 30);
			ghost_dy = 0;
		}
		else if (temp == 2) { //Ghost appears top side
			ghost_x = rnd->Next(1, 600);
			ghost_y = 1;
			ghost_dx = 0;
			ghost_dy = rnd->Next(10, 30);
		}
		else if (temp == 3) { //Ghost appears down side
			ghost_x = rnd->Next(1, 600);
			ghost_y = 600;
			ghost_dx = 0;
			ghost_dy = -rnd->Next(10, 30);
		}
		arrEntity.push_back(new Ghost(ghost_x, ghost_y, 1, 1));
		arrEntity.at(arrEntity.size() - 1)->new_dx(ghost_dx);
		arrEntity.at(arrEntity.size() - 1)->new_dy(ghost_dy);
		delete rnd;
	}
	for (int i = 0; i < arrEntity.size(); i++) {
		if (arrEntity.at(i)->return_flag())
			arrEntity.erase(arrEntity.begin() + i);
	}
}
void Game::Draw_Player(Graphics^ g, Bitmap^ bmp) {
	objPlayer->Move(g);
	objPlayer->Draw_from_image(g, bmp);
}
void Game::Draw_Vector(Graphics^ g, Bitmap^ bmpGhost, Bitmap^ bmpFireball) {
	for (int i = 0; i < arrEntity.size(); i++) {
		if (dynamic_cast<Ghost*> (arrEntity.at(i))) {
			arrEntity.at(i)->Move(g);
			arrEntity.at(i)->Draw_from_image(g, bmpGhost);
		}
		else {
			arrEntity.at(i)->Move(g);
			arrEntity.at(i)->Draw_from_image(g, bmpFireball);
		}
	}
}
void Game::Shoot() {
	arrEntity.push_back(new Fireball(objPlayer->return_x(), objPlayer->return_y(), 1, 1, objPlayer->return_orientation()));
}
void Game::Colision() {
	for (int i = 0; i < arrEntity.size(); i++) {
		if (dynamic_cast<Ghost*> (arrEntity.at(i))) {
			//If player hits ghost lifes decrease and ghost dissapears
			if (objPlayer->return_rectangle().IntersectsWith(arrEntity.at(i)->return_rectangle())) {
				objPlayer->new_lifes(objPlayer->return_lifes() - 1);
				arrEntity.erase(arrEntity.begin() + i);
				continue;
			}
			//If ghost hits fireball the ghost dissapears
			for (int j = i; j < arrEntity.size(); j++) {
				if (dynamic_cast<Fireball*> (arrEntity.at(j)) && arrEntity.at(i)->return_rectangle().IntersectsWith(arrEntity.at(j)->return_rectangle())) {
					arrEntity.erase(arrEntity.begin() + i);
					points++;
				}
			}
		}
	}
}
bool Game::End_Game() {
	if (objPlayer->return_lifes() <= 0)
		return true;
	return false;
}
void Game::new_orientation(direction new_data) {
	objPlayer->new_orientation(new_data);
}
System::String^ Game::return_text_lifes() {
	System::String^ phrase = "Lifes = ";
	System::String^ lifes_text = (objPlayer->return_lifes()).ToString();
	phrase += lifes_text;
	return phrase;
}
System::String^ Game::return_text_points() {
	System::String^ phrase = "Points = ";
	System::String^ points_text = points.ToString();
	phrase += points_text;
	return phrase;
}