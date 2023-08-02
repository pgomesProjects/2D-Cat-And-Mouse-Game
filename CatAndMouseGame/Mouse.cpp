//Headers
#include "Mouse.h"

Mouse::Mouse(int speed, float scentDepletionRate): Entity(pieces["mouse"].first, speed) {
	this->speed = speed;
	this->scentDepletionRate = scentDepletionRate;
}

bool Mouse::CheckForFood(Maze& currentMaze) {
	//If the mouse is on a piece that has food in it, consume the piece and then let the game know that food was found
	if (currentMaze.GetCell(this->position.first, this->position.second).ContainsPiece(pieces["food"].first)) {
		currentMaze.GetCell(this->position.first, this->position.second).RemovePiece(pieces["food"].first);
		return true;
	}

	return false;
}

bool Mouse::Move(Maze& currentMaze, int row, int col) {
	bool moveSuccessful = false;

	for (int i = 0; i < this->speed; i++) {
		int newX = this->position.first + row;
		int newY = this->position.second + col;

		//If the new position for the entity is not out of bounds and is either an empty / food space, allow the entity to move there
		if (newX >= 0 && newX < currentMaze.GetCols() && newY >= 0 && newY < currentMaze.GetRows()) {
			if ((currentMaze.GetCell(newX, newY).GetTopPiece() == pieces["emptySpace"].first) || (currentMaze.GetCell(newX, newY).GetTopPiece() == pieces["food"].first)) {
				UpdateScentTrail(currentMaze);
				SetPosition(currentMaze, { newX, newY });
				moveSuccessful = true;
			}
		}
	}

	return moveSuccessful;
}

void Mouse::PrintScentTrail() {
	cout << "Trail: ";
	for (const auto& trail : this->scentTrail) {
		cout << trail->GetScentStrength() << ", ";
	}
}

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
