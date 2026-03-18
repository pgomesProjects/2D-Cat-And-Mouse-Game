#include "console.h"
#include <iostream>
#include <windows.h> //WinApi header

using std::cout;
using std::endl;

void console::ClearScreen() {
	//Clear the console
	system("cls");
}

void console::PrintColorText(string text, TEXTCOLORS color) {
	//Set the color of the text and print it
	SetConsoleColor(color);
	cout << text;

	//Reset the text color
	SetConsoleColor(console::WHITE);
}

void console::SetConsoleColor(TEXTCOLORS color) {
	//Set color of the console text / background
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}