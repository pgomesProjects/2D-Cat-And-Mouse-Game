#pragma once
#include <map>
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::map;
using std::pair;
using std::string;
using std::vector;

//Global declarations for Maze piece characters
extern map<string, pair<char, int>> pieces;

class Cell {
public:
	//Constructors
	Cell();
	Cell(char piece);
	Cell(char piece, float scentStrength);

	void AddPiece(char piece);
	void RemovePiece(char piece);

	//GETTERS
	char GetTopPiece();
	bool ContainsPiece(char piece);
	float GetScentStrength();

	//SETTERS
	void SetScentStrength(float scentStrength);

private:
	vector<pair<char, int>> pieceList;
	float scentStrength;

	int GetPiecePriority(char piece);
};