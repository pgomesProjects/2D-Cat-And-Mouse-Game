#include "console.h"
#include <iostream>
#include <windows.h> //WinApi header

using std::cout;
using std::endl;

void console::ClearScreen() {
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Get the console size
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	//Fill the console with blank spaces
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);

	//Resets all of the console outputs to remove any color
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	//Move the cursor to the top left
	SetConsoleCursorPosition(hConsole, coordScreen);
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