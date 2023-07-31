//Headers
#include "Cell.h"

char wall = '#';
char emptySpace = '.';
char mouse = 'M';
char cat = 'C';
char food = 'F';

Cell::Cell() {
	this->piece = wall;
	this->scentStrength = 0;
}

Cell::Cell(char piece) {
	this->piece = piece;
	this->scentStrength = 0;
}

Cell::Cell(char piece, float scentStrength) {
	this->piece = piece;
	this->scentStrength = scentStrength;
}

char Cell::GetPiece() {
	return this->piece;
}

float Cell::GetScentStrength() {
	return this->scentStrength;
}

void Cell::SetPiece(char piece) {
	this->piece = piece;
}

void Cell::SetScentStrength(float scentStrength) {
	this->scentStrength = scentStrength;
}