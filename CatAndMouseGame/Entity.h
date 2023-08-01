#pragma once
#include <vector>
using std::pair;

//Headers
#include "Maze.h"

class Entity {
public:
	Entity(char icon);
	Entity(char icon, int speed);

	virtual bool Move(Maze& currentMaze, int row, int col);
	virtual void SetPosition(Maze& currentMaze, pair<int, int> position);

	//GETTERS
	pair<int, int>GetPosition();

protected:
	char icon;
	int speed;
	pair<int, int> position;
};