#pragma once
#include <vector>
using std::pair;

//Headers
#include "Maze.h"

class Entity {
public:
	//Constructors
	Entity(char icon);
	Entity(char icon, int speed);

	//Moves the Entity a set amount of units in the maze
	virtual bool Move(Maze& currentMaze, int row, int col);

	//Sets the position of the Entity in the maze
	virtual void SetPosition(Maze& currentMaze, pair<int, int> position);

	//GETTERS
	pair<int, int>GetPosition();

protected:
	char icon;
	int speed;
	pair<int, int> position;
};