//Headers
#include "Food.h"

Food::Food(int x, int y) {
	this->icon = pieces["food"].first;
	this->position = { x, y };
}

void Food::PlaceFood(Maze& currentMaze) {
	currentMaze.GetCell(this->position.first, this->position.second).AddPiece(this->icon);
}