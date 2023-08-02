//Headers
#include "Food.h"

Food::Food(int x, int y) {
	this->icon = pieces["food"].first;
	this->position = { x, y };
}

/// <summary>
/// Places food in the maze at the position given to the object.
/// </summary>
/// <param name="currentMaze">The data for the maze to place the food in.</param>
void Food::PlaceFood(Maze& currentMaze) {
	currentMaze.GetCell(this->position.first, this->position.second).AddPiece(this->icon);
}