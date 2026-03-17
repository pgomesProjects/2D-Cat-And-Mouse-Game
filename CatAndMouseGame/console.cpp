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

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '),
		dwConSize,
		coordScreen,
		&cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole,
		csbi.wAttributes,
		dwConSize,
		coordScreen,
		&cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void console::PrintColorText(string text, TEXTCOLORS color) {
	//Set the color of the text and print it
	setrgb(color);
	cout << text;

	//Reset the text color
	setrgb(console::WHITE);
}

void console::setrgb(TEXTCOLORS color) {
	//Set color of text
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}