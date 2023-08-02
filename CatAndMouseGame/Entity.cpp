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

/// <summary>
/// Moves the Entity in a given direction.
/// </summary>
/// <param name="currentMaze">The data for the maze to move in.</param>
/// <param name="row">The amount of units to move the Entity in the row.</param>
/// <param name="col">The amount of units to move the Entity in the column.</param>
/// <returns>If true, the Entity has successfully moved.</returns>
bool Entity::Move(Maze& currentMaze, int row, int col) {

	bool moveSuccessful = false;

	//Move the Entity in the direction X amount of times (X is determined by speed)
	for (int i = 0; i < this->speed; i++) {

		int newX = this->position.first + row;
		int newY = this->position.second + col;

		//If the new position for the entity is not out of bounds and is either an empty / food space, allow the entity to move there
		if (newX >= 0 && newX < currentMaze.GetCols() && newY >= 0 && newY < currentMaze.GetRows() && (currentMaze.GetCell(newX, newY).GetTopPiece() == pieces["emptySpace"].first) || (currentMaze.GetCell(newX, newY).GetTopPiece() == pieces["food"].first)) {
			SetPosition(currentMaze, { newX, newY });
			moveSuccessful = true;
		}
	}

	return moveSuccessful;
}

/// <summary>
/// Sets the position of the Entity in the maze, moving it from one cell to another.
/// </summary>
/// <param name="currentMaze">The data for the maze.</param>
/// <param name="position">The new position for the Entity.</param>
void Entity::SetPosition(Maze& currentMaze, pair<int, int> position) {
	//Remove the Entity from their current position
	currentMaze.GetCell(this->position.first, this->position.second).RemovePiece(this->icon);
	
	//Update the position and add the Entity to the new position
	this->position = position;
	currentMaze.GetCell(this->position.first, this->position.second).AddPiece(this->icon);
}

pair<int, int> Entity::GetPosition() {
	return this->position;
}