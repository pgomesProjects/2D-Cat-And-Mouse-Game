//Headers
#include "Mouse.h"

Mouse::Mouse(int speed, float scentDepletionRate): Entity(pieces["mouse"].first, speed) {
	this->speed = speed;
	this->scentDepletionRate = scentDepletionRate;
}

/// <summary>
/// Checks to see if the player picked up food.
/// </summary>
/// <param name="currentMaze">The data for the maze.</param>
/// <returns>If true, the cell that the player is on contains food.</returns>
bool Mouse::CheckForFood(Maze& currentMaze) {

	//If the mouse is on a piece that has food in it, consume the piece and then let the game know that food was found
	if (currentMaze.GetCell(this->position.first, this->position.second).ContainsPiece(pieces["food"].first)) {
		currentMaze.GetCell(this->position.first, this->position.second).RemovePiece(pieces["food"].first);
		return true;
	}

	return false;
}

/// <summary>
/// Moves the Mouse in a given direction and produces a scent trail.
/// </summary>
/// <param name="currentMaze">The data for the maze to move in.</param>
/// <param name="row">The amount of units to move the Entity in the row.</param>
/// <param name="col">The amount of units to move the Entity in the column.</param>
/// <returns>If true, the Entity has successfully moved.</returns>
bool Mouse::Move(Maze& currentMaze, int row, int col) {
	
	bool moveSuccessful = false;

	//Move the Entity in the direction X amount of times (X is determined by speed)
	for (int i = 0; i < this->speed; i++) {
		int newX = this->position.first + row;
		int newY = this->position.second + col;

		//If the new position for the entity is not out of bounds and is either an empty / food space, allow the entity to move there
		if (newX >= 0 && newX < currentMaze.GetRows() && newY >= 0 && newY < currentMaze.GetCols()) {
			if ((currentMaze.GetCell(newX, newY).GetTopPiece() == pieces["emptySpace"].first) || (currentMaze.GetCell(newX, newY).GetTopPiece() == pieces["food"].first)) {
				//Update the scent trail before moving
				UpdateScentTrail(currentMaze);

				SetPosition(currentMaze, { newX, newY });
				moveSuccessful = true;
			}
		}
	}

	return moveSuccessful;
}

/// <summary>
/// Prints the scent trail data to the console (for debugging purposes).
/// </summary>
void Mouse::PrintScentTrail() {
	cout << "Trail: ";
	for (const auto& trail : this->scentTrail) {
		cout << trail->GetScentStrength() << ", ";
	}
}

/// <summary>
/// Updates the mouse's scent trail via adding new scents and depleting older scents.
/// </summary>
/// <param name="currentMaze">The data for the maze.</param>
void Mouse::UpdateScentTrail(Maze& currentMaze) {

	//Deplete any existing trail scents
	for (int i = 0; i < this->scentTrail.size(); i++)
		this->scentTrail[i]->SetScentStrength(this->scentTrail[i]->GetScentStrength() - this->scentDepletionRate);

	//Add a scent to the current cell of the player
	Cell* newestCell = &currentMaze.GetCell(this->position.first, this->position.second);
	newestCell->SetScentStrength(MAX_TRAIL_SCENT);

	//Find the cell in the scent trail list
	auto it = std::find(this->scentTrail.begin(), this->scentTrail.end(), newestCell);

	//If the cell is not found in the current scent trail, add it to the scent trail
	if (it == this->scentTrail.end()) {
		this->scentTrail.push_back(newestCell);
	}

	//Remove any scents in the scent trail that have no more scent
	this->scentTrail.erase(std::remove_if(this->scentTrail.begin(), this->scentTrail.end(),
		[](Cell* cell) {
			float currentScent = cell->GetScentStrength();
			return currentScent <= 0;
		}),
		this->scentTrail.end());
}
