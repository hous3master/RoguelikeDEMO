#include "Ghost.h"
Ghost::Ghost(){}
Ghost::Ghost(int px, int py, int pw, int ph) : Entity(px, py, pw, ph, 1, 1, 0, 0) {}
Ghost::~Ghost(){}