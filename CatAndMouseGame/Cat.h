#pragma once
#include <algorithm>
#include <vector>
using std::pair;
using std::shuffle;
using std::vector;

//Headers
#include "Entity.h"
#include "Maze.h"

class Cat : public Entity {
public:
	Cat();
	Cat(int speed, float chanceForExtraMovement);

	bool CheckForMovement(Maze& currentMaze);

	bool CanSmellPlayer();

private:
	float chanceForExtraMovement;
	bool canSmellPlayer;
};