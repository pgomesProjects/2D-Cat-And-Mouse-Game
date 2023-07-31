#pragma once
#include <vector>
using std::pair;
using std::vector;

//Headers
#include "Maze.h"

class Mouse {
public:
	void Move(Maze& currentMaze, int row, int col);
	void SetPosition(Maze &currentMaze, pair<int, int> position);

private:
	pair<int, int> position;
	vector<Cell> scentTrail;
};