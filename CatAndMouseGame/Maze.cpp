//Headers
#include "Maze.h"

//Random device used for seeding
std::random_device rd;
std::mt19937 gen(rd());

Maze::Maze(int size) {
	this->rows = size;
	this->cols = size;
	this->spacingX = 1;
	this->spacingY = 1;
	PopulateMaze();
	GenerateMaze(entrance.first, entrance.second);
}

Maze::Maze(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	this->spacingX = 1;
	this->spacingY = 1;
	PopulateMaze();
	GenerateMaze(entrance.first, entrance.second);
}

Maze::Maze(int rows, int cols, int spacing) {
	this->rows = rows;
	this->cols = cols;
	this->spacingX = spacing;
	this->spacingY = spacing;
	PopulateMaze();
	GenerateMaze(entrance.first, entrance.second);
}

Maze::Maze(int rows, int cols, int spacingX, int spacingY) {
	this->rows = rows;
	this->cols = cols;
	this->spacingX = spacingX;
	this->spacingY = spacingY;
	PopulateMaze();
	GenerateMaze(entrance.first, entrance.second);
}

/// <summary>
///	Initializes the maze and populates it with wall objects.
/// </summary>
void Maze::PopulateMaze() {
	
	this->mazeData = new Cell[rows * cols];
}

/// <summary>
/// Generates a maze layout through checking adjacent spaces.
/// </summary>
/// <param name="x">The current x position of the maze.</param>
/// <param name="y">The current y position of the maze.</param>
void Maze::GenerateMaze(int x, int y) {

	//Set the current space as empty
	*(this->mazeData + x * cols + y) = emptySpace;

	//Randomly check the spaces around the current space (up, down, left, right)
	vector<pair<int, int>> adjacent = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	shuffle(adjacent.begin(), adjacent.end(), gen);

	//For each direction
	for (const auto& dir : adjacent) {
		
		int newX = x + 2 * dir.first;
		int newY = y + 2 * dir.second;

		//If the position being checked is not out of bounds and is a wall piece, make it an empty piece and make the path between the cells an empty piece
		if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && this->mazeData[newX * cols + newY].GetPiece() == wall) {
			this->mazeData[newX * cols + newY].SetPiece(emptySpace);
			this->mazeData[(x + dir.first) * this->cols + (y + dir.second)].SetPiece(emptySpace);

			//Check the new position's adjacent positions
			GenerateMaze(newX, newY);
		}
	}
}

/// <summary>
/// Gets a position in the maze within a distance from the player.
/// </summary>
/// <param name="icon">The icon of the item to place.</param>
/// <param name="playerPosition">The position of the player.</param>
/// <param name="distanceBuffer">The minimum distance between the player and the item to place.</param>
/// <returns>The position in the maze that is empty.</returns>
pair<int, int> Maze::GetEmptyPositionInMaze(pair<int, int> playerPosition, int distanceBuffer) {
	
	//Find all valid empty spaces within the maze
	vector<pair<int, int>> emptySpaces;
	
	for (int x = 0; x < this->rows; x++) {
		for (int y = 0; y < this->cols; y++) {
			//If the current space is an empty space and is the correct distance from the player, add to the list
			if (this->mazeData[x * this->cols + y].GetPiece() == emptySpace && GetDistanceFrom({x, y}, playerPosition) >= distanceBuffer) {
				emptySpaces.push_back({x, y});
			}
		}
	}

	//If there are spaces to place the item, choose one at random
	if (!emptySpaces.empty()) {
		std::uniform_int_distribution<int> dist(0, emptySpaces.size() - 1);
		return emptySpaces[dist(gen)];
	}

	else
		return { -1, -1 };

}

int Maze::GetDistanceFrom(const pair<int, int>& firstCell, const pair<int, int>& secondCell) {
	return abs(secondCell.first - firstCell.first) + abs(secondCell.second - firstCell.second);
}

/// <summary>
/// Prints out the maze to the console with spacing.
/// </summary>
void Maze::Print() {

	for (int x = 0; x < this->rows; x++) {
		
		for (int y = 0; y < this->cols; y++) {

			cout << this->mazeData[x * this->cols + y].GetPiece();

			//Add spaces between each column as needed
			for (int s = 0; s < this->spacingX; s++) {
				cout << " ";
			}
		}

		//Always have one break between rows
		cout << endl;

		//Add additonal spaces between rows as needed
		for (int s = 1; s < this->spacingY; s++) {
			cout << endl;
		}
	}
}

pair<int, int> Maze::GetEntrance() {
	return this->entrance;
}

Cell& Maze::GetCell(int row, int col) {
	return this->mazeData[row * cols + col];
}

int Maze::GetRows() {
	return this->rows;
}

int Maze::GetCols() {
	return this->cols;
}

Maze::~Maze() {
	delete this->mazeData;
}