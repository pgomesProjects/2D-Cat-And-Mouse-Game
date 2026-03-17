#pragma once
#include "console.h"
#include <map>
#include <iostream>
#include <vector>
using std::cout;
using std::map;
using std::pair;
using std::vector;

//Global declarations for Maze piece characters
extern map<string, pair<char, int>> pieces;

class Cell {
public:
	//Constructors
	Cell();
	Cell(char piece);
	Cell(char piece, float scentStrength);

	/// <summary>
	/// Adds a piece to the cell.
	/// </summary>
	/// <param name="piece">The character value for the piece.</param>
	void AddPiece(char piece);

	/// <summary>
	/// Removes a piece from the cell.
	/// </summary>
	/// <param name="piece">The character value for the piece.</param>
	void RemovePiece(char piece);

	/// <summary>
	/// Prints the cell data to the console.
	/// </summary>
	void PrintCell();

	//GETTERS
	char GetTopPiece();
	bool ContainsPiece(char piece);
	float GetScentStrength();

	//SETTERS
	void SetScentStrength(float scentStrength);

private:
	vector<pair<char, int>> pieceList;
	float scentStrength;

	//Gets a piece's priority based on the character data given
	int GetPiecePriority(char piece);
};