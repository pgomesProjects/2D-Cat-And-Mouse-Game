//Headers
#include "Cell.h"

map<string, pair<char, int>>pieces = {
	{"cat", {'C', 0}},
	{"mouse", {'M', 1}},
	{"food", {'F', 2}},
	{"emptySpace", {'.', 3}},
	{"wall", {'#', 4}}
};

Cell::Cell() {
	AddPiece(pieces["wall"].first);
	this->scentStrength = 0;
}

Cell::Cell(char piece) {
	AddPiece(pieces["wall"].first);
	AddPiece(piece);
	this->scentStrength = 0;
}

Cell::Cell(char piece, float scentStrength) {
	AddPiece(pieces["wall"].first);
	AddPiece(piece);
	this->scentStrength = scentStrength;
}

void Cell::AddPiece(char piece) {

	//Get the priority number from the pre-defined list of pieces
	int priority = GetPiecePriority(piece);

	//Iterates through the existing list (which is assumed to be sorted) and gets the position of where the piece needs to be at
	auto it = this->pieceList.begin();
	while (it != this->pieceList.end() && it->second < priority) {
		++it;
	}

	this->pieceList.insert(it, { piece, priority });
}

void Cell::RemovePiece(char piece) {

	pair<char, int> currentPiece = { piece, GetPiecePriority(piece) };

	//Find the character in the piece list and remove it if it's in there
	auto it = std::find(this->pieceList.begin(), this->pieceList.end(), currentPiece);
	if (it != this->pieceList.end()) {
		this->pieceList.erase(it);
	}
}

/// <summary>
/// Returns the priority of the piece in order of how it should be shown on the map.
/// </summary>
/// <param name="piece">The character data for the piece.</param>
/// <returns>If the piece is not in the list of defined pieces, returns -1. Else, it returns the priority stored in the pre-defined list.</returns>
int Cell::GetPiecePriority(char piece) {

	//Find the priority of the piece given
	int priorityValue = -1;

	for (const auto& p : pieces) {
		if (p.second.first == piece) {
			priorityValue = p.second.second;
			break;
		}
	}

	return priorityValue;
}

char Cell::GetTopPiece() {
	return this->pieceList[0].first;
}

bool Cell::ContainsPiece(char piece) {
	pair<char, int> currentPiece = { piece, GetPiecePriority(piece) };

	//Find the character in the piece list and return true or false if found
	auto it = std::find(this->pieceList.begin(), this->pieceList.end(), currentPiece);
	return it != this->pieceList.end();
}

float Cell::GetScentStrength() {
	return this->scentStrength;
}

void Cell::SetScentStrength(float scentStrength) {
	this->scentStrength = scentStrength;
}