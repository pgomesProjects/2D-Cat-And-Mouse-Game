#pragma once

#include <string>
using std::string;

class console {
public:
	/// <summary>
	/// The colors options for the text.
	/// </summary>
	enum TEXTCOLORS { 
		DARKBLUE = 1, 
		DARKGREEN = 2, 
		DARKTEAL = 3, 
		DARKRED = 4, 
		DARKMAGENTA = 5, 
		DARKYELLOW = 6, 
		LIGHTGRAY = 7,
		GRAY = 8,
		BLUE = 9, 
		GREEN = 10, 
		TEAL = 11, 
		RED = 12, 
		MAGENTA = 13,
		YELLOW = 14, 
		WHITE = 15 
	};

	/// <summary>
	/// Clears the screen.
	/// </summary>
	static void ClearScreen();

	/// <summary>
	/// Prints a string of text in color on the console.
	/// </summary>
	/// <param name="text">The text to colorize.</param>
	/// <param name="color">The color for the text.</param>
	static void PrintColorText(string text, TEXTCOLORS color);

private:
	/// <summary>
	/// Sets the text and background colors.
	/// </summary>
	/// <param name="color">The option for the color of the text.</param>
	static void setrgb(TEXTCOLORS color);
};