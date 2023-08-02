#pragma once
#include <vector>
using std::pair;

//Headers
#include "Maze.h"

class Food {
public:
	Food(int x, int y);
	void PlaceFood(Maze& currentMaze);

private:
	char icon;
	pair<int, int> position;
};