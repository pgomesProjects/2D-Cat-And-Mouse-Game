#pragma once
#include <vector>
using std::pair;
using std::vector;

//Headers
#include "Entity.h"
#include "Maze.h"

class Mouse : public Entity {
public:
	Mouse();
	Mouse(int speed);

private:
	vector<Cell> scentTrail;
};