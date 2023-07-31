#pragma once
#include <string>
using std::string;

//Global declarations for Maze piece characters
extern char wall;
extern char emptySpace;
extern char mouse;
extern char cat;
extern char food;

class Cell {
public:
	//Constructors
	Cell();
	Cell(char piece);
	Cell(char piece, float scentStrength);

	//GETTERS
	char GetPiece();
	float GetScentStrength();

	//SETTERS
	void SetPiece(char piece);
	void SetScentStrength(float scentStrength);

private:
	char piece;
	float scentStrength;
};