//Headers
#include "Cat.h"

Cat::Cat() : Entity(pieces["cat"].first) {
	this->speed = 1;
	this->chanceForExtraMovement = 0;
	this->canSmellPlayer = false;
}

Cat::Cat(int speed, float chanceForExtraMovement) : Entity(pieces["cat"].first, speed) {
	this->speed = speed;
	this->chanceForExtraMovement = chanceForExtraMovement;
	this->canSmellPlayer = false;
}

/// <summary>
/// Checks to see if the Cat has any potential areas for movement and whether they can capture the player.
/// </summary>
/// <param name="currentMaze">The data for the maze.</param>
/// <returns>If true, the cat has captured the player.</returns>
bool Cat::CheckForMovement(Maze& currentMaze) {
	
	//Random device used for seeding
	std::random_device rd;
	std::mt19937 gen(rd());

	//Add a chance for the cat to move one extra time based on its properties
	int extraMovements = 0;
	std::uniform_int_distribution<int> dist(0, 100);
	float chanceToMove = (float)dist(gen);
	if (chanceToMove < chanceForExtraMovement * 100)
		extraMovements++;

	//Moves the cat based on the speed and adds any extra movements that may be applicable
	for (int i = 0; i < this->speed + extraMovements; i++) {

		vector<pair<int, int>> adjacent = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		vector<pair<int, int>> possibleMovements;

		//For each direction, check to see where the cat can move
		for (const auto& dir : adjacent) {

			int newX = this->position.first + dir.first;
			int newY = this->position.second + dir.second;

			//If the position being checked is not out of bounds and is a not a wall piece, add it to the list of possible movement options
			if (newX >= 0 && newX < currentMaze.GetRows() && newY >= 0 && newY < currentMaze.GetCols() && currentMaze.GetCell(newX, newY).GetTopPiece() != pieces["wall"].first) {

				//If the cat can catch the mouse, immediately end the game
				if (currentMaze.GetCell(newX, newY).GetTopPiece() == pieces["mouse"].first) {
					return true;
				}

				//Add to the list of possible movements
				possibleMovements.push_back({ newX, newY });
			}
		}

		if (!possibleMovements.empty()) {

			//Go through the list of possible movements
			int moveIndex = -1;
			for (int i = 0; i < possibleMovements.size(); i++) {
				//If there's been a scent picked up already, but there's a stronger scent in another direction, switch directions
				if (moveIndex >= 0 && currentMaze.GetCell(possibleMovements[i].first, possibleMovements[i].second).GetScentStrength() > currentMaze.GetCell(possibleMovements[moveIndex].first, possibleMovements[moveIndex].second).GetScentStrength()) {
					moveIndex = i;
				}
				//If there is a scent on any cell nearby, set the direction to the direction of the scent
				else if (moveIndex < 0 && currentMaze.GetCell(possibleMovements[i].first, possibleMovements[i].second).GetScentStrength() > 0) {
					moveIndex = i;
				}
			}

			//If the move index has changed, a smell has been found
			this->canSmellPlayer = moveIndex >= 0;

			//If no scent has been found, move the cat in a random direction from the list of movement options (simplistic movement for demonstration purposes)
			if (!this->canSmellPlayer) {
				std::uniform_int_distribution<int> dist(0, (int)possibleMovements.size() - 1);
					moveIndex = dist(gen);
			}

			//Move the cat either randomly or in the direction of a scent
			SetPosition(currentMaze, possibleMovements[moveIndex]);

		}
	}

	return false;
}

bool Cat::CanSmellPlayer() {
	return this->canSmellPlayer;
;}