#include "Creature.h"


void Creature::Move() {
    PrevX = X; // Set prevX before updating x
	PrevY = Y; // Set prevY before updating y
	X += xMove;
	Y += yMove;
}