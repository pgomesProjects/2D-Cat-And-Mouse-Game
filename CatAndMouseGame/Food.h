#pragma once
#include <vector>
using std::pair;

//Headers
#include "Maze.h"

class Food {
public:
	//Constructors
	Food(int x, int y);

	//Places food in the maze
	void PlaceFood(Maze& currentMaze);

private:
	char icon;
	pair<int, int> position;
};