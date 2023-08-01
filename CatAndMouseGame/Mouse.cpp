//Headers
#include "Mouse.h"

Mouse::Mouse(): Entity(mouse) {
	this->speed = 1;
}

Mouse::Mouse(int speed): Entity(mouse, speed) {
	this->speed = speed;
}