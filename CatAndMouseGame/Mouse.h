#pragma once
#include <vector>
using std::pair;
using std::vector;

//Headers
#include "Entity.h"
#include "Maze.h"

const float MAX_TRAIL_SCENT = 1.0f;

class Mouse : public Entity {
public:
	Mouse(int speed, float scentDepletionRate);

	bool CheckForFood(Maze& currentMaze);
	bool Move(Maze& currentMaze, int row, int col) override;

	void PrintScentTrail();

private:
	vector<Cell*> scentTrail;
	float scentDepletionRate;

	void UpdateScentTrail(Maze& currentMaze);
};