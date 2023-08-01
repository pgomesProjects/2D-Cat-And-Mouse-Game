//Headers
#include "Entity.h"

Entity::Entity(char icon) {
	this->icon = icon;
	this->speed = 1;
}

Entity::Entity(char icon, int speed) {
	this->icon = icon;
	this->speed = speed;
}

bool Entity::Move(Maze& currentMaze, int row, int col) {

	bool moveSuccessful = false;

	for (int i = 0; i < this->speed; i++) {
		int newX = this->position.first + row;
		int newY = this->position.second + col;

		if (newX >= 0 && newX < currentMaze.GetRows() && newY >= 0 && newY < currentMaze.GetCols() && currentMaze.GetCell(newX, newY).GetPiece() == emptySpace) {
			SetPosition(currentMaze, { newX, newY });
			moveSuccessful = true;
		}
	}

	return moveSuccessful;
}

void Entity::SetPosition(Maze& currentMaze, pair<int, int> position) {
	currentMaze.GetCell(this->position.first, this->position.second).SetPiece(emptySpace);
	this->position = position;
	currentMaze.GetCell(this->position.first, this->position.second).SetPiece(this->icon);
}

pair<int, int> Entity::GetPosition() {
	return this->position;
}