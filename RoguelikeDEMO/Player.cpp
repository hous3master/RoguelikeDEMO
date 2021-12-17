#include "Player.h"
Player::Player() {}
Player::Player(int px, int py, int pw, int ph) : Entity(px, py, pw, ph, 4, 4, 0, 0) {
	lifes = 3;
	vertical_velocity = 14;
	horizontal_velocity = 14;
	new_orientation(direction::still);
}
Player::~Player() {}
void Player::new_lifes(int new_data) { lifes = new_data; }
int Player::return_lifes() { return lifes; }
