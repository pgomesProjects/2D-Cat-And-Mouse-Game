//Headers
#include "Cat.h"

Cat::Cat() : Entity(cat) {
	this->speed = 1;
	this->chanceForExtraMovement = 0;
}

Cat::Cat(int speed, float chanceForExtraMovement) : Entity(cat, speed) {
	this->speed = speed;
	this->chanceForExtraMovement = chanceForExtraMovement;
}

bool Cat::CheckForMovement(Maze& currentMaze) {
	
	//Random device used for seeding
	std::random_device rd;
	std::mt19937 gen(rd());

	//Add a chance for the cat to move one extra time based on its properties
	int extraMovements = 0;
	std::uniform_int_distribution<int> dist(0, 100);
	float chanceToMove = dist(gen);
	if (chanceToMove < chanceForExtraMovement * 100)
		extraMovements++;

	for (int i = 0; i < this->speed + extraMovements; i++) {
		vector<pair<int, int>> adjacent = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

		vector<pair<int, int>> possibleMovements;

		//For each direction, check to see where the cat can move
		for (const auto& dir : adjacent) {

			int newX = this->position.first + dir.first;
			int newY = this->position.second + dir.second;

			//If the position being checked is not out of bounds and is a not a wall piece, add it to the list of possible movement options
			if (newX >= 0 && newX < currentMaze.GetRows() && newY >= 0 && newY < currentMaze.GetCols() && currentMaze.GetCell(newX, newY).GetPiece() != wall) {

				//If the cat can catch the mouse, immediately end the game
				if (currentMaze.GetCell(newX, newY).GetPiece() == mouse) {
					return true;
				}

				possibleMovements.push_back({ newX, newY });
			}
		}

		if (!possibleMovements.empty()) {
			std::uniform_int_distribution<int> dist(0, possibleMovements.size() - 1);
			SetPosition(currentMaze, possibleMovements[dist(gen)]);
		}
	}

	return false;
}