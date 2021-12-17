#include "Fireball.h"
Fireball::Fireball() {}
Fireball::Fireball(int px, int py, int pw, int ph, direction player_orientation) : Entity(px, py, pw, ph, 1, 4, 0, 0) {
	if (player_orientation == direction::up) {
		dx = 0;
		dy = -30;
	}
	else if (player_orientation == direction::down) {
		dx = 0;
		dy = 30;
	}
	else if (player_orientation == direction::left) {
		dx = -30;
		dy = 0;
	}
	else if (player_orientation == direction::right) {
		dx = 30;
		dy = 0;
	}
}
Fireball::~Fireball() {}
