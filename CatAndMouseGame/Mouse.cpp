//Headers
#include "Mouse.h"

void Mouse::Move(Maze &currentMaze, int row, int col) {
	int newX = this->position.first + row;
	int newY = this->position.second + col;

	if (newX >= 0 && newX < currentMaze.GetRows() && newY >= 0 && newY < currentMaze.GetCols() && currentMaze.GetCell(newX, newY).GetPiece() == emptySpace) {
		SetPosition(currentMaze, { newX, newY });
	}
}

void Mouse::SetPosition(Maze &currentMaze, pair<int, int> position) {
	currentMaze.GetCell(this->position.first, this->position.second).SetPiece(emptySpace);
	this->position = position;
	currentMaze.GetCell(this->position.first, this->position.second).SetPiece(mouse);
}