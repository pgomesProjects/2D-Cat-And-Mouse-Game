#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using std::abs;
using std::cout;
using std::endl;
using std::pair;
using std::shuffle;
using std::vector;

//Headers
#include "Cell.h"

class Maze {
public:
	//Constructors
	Maze(int size);
	Maze(int rows, int cols);
	Maze(int rows, int cols, int spacing);
	Maze(int rows, int cols, int spacingX, int spacingY);

	//Gets an empty position in the maze within a distance from the player
	pair<int, int> GetEmptyPositionInMaze(pair<int, int> playerPosition, int distanceBuffer);

	//Prints array
	void Print();

	//GETTERS
	pair<int, int> GetEntrance();
	Cell& GetCell(int row, int col);
	int GetRows();
	int GetCols();

	//Destructors
	~Maze();

private:	
	const pair<int, int> entrance = {1, 1};

	int rows;
	int cols;
	int spacingX;
	int spacingY;
	Cell* mazeData;

	//Populates the maze with data
	void PopulateMaze();
	//Generates the maze
	void GenerateMaze(int x, int y);
	//Calculates the distance between two cells
	int GetDistanceFrom(const pair<int, int>& firstCell, const pair<int, int>& secondCell);
};