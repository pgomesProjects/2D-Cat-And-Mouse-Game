#pragma once
#include <vector>
using std::pair;
using std::vector;

//Headers
#include "Entity.h"
#include "Maze.h"

//Constant variable reference for the maximum trail scent value
const float MAX_TRAIL_SCENT = 1.0f;

class Mouse : public Entity {
public:
	//Constructors
	Mouse(int speed, float scentDepletionRate);

	//Checks to see if the player can pick up food
	bool CheckForFood(Maze& currentMaze);

	//Overrides the Move function to incorporate scent trail logic
	bool Move(Maze& currentMaze, int row, int col) override;

	//Prints the scent trail's values (for debugging purposes)
	void PrintScentTrail();

private:
	vector<Cell*> scentTrail;
	float scentDepletionRate;

	//Updates the scent trail before movement
	void UpdateScentTrail(Maze& currentMaze);
};